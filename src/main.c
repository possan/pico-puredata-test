#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#if PICO
#include <malloc.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include <pico/bootrom.h>

#include "hardware/gpio.h"
#include "hardware/exception.h"
#include "hardware/watchdog.h"

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "m0FaultDispatch.h"
#endif

// #include "FreeRTOS_POSIX.h"
// #include "FreeRTOS_POSIX/sys/types.h"
// #include "FreeRTOS_POSIX/time.h"
// #include "FreeRTOS_POSIX/pthread.h"
// #include "FreeRTOS_POSIX/sched.h"
// #include <FreeRTOS_POSIX_portable.h>
// #include "FreeRTOS_POSIX/pthread.h"
// #include <lib.h>

#include <z_libpd.h>
#include <z_print_util.h>

#include "g_canvas.h"

#include "espd.h"

// sed 's/;$/;\\/' foo.pd | sed 's/#N //'
static const char patchfile[] =
  "canvas 0 50 450 300 12;\n\
  #X obj 190 104 loadbang;\n\
  #X msg 190 129; pd dsp 1;\n\
  #X obj 118 123 dac~ 1;\n\
  #X obj 118 98 osc~ 440;\n\
  #X connect 0 0 1 0;\n\
  #X connect 3 0 2 0;\n\
  ";

extern void mess_init(void);
extern void sched_init(void);
extern void obj_init(void);
extern void conf_init(void);
extern void sys_lock(void);

void pdprint1(const char *s)
{
  printf("pd1: %s\n", s);
}

void pdprint2(const char *s)
{
  printf("pd2: %s\n", s);
}

void pdnoteon1(int ch, int pitch, int vel)
{
  printf("pd1 noteon: %d %d %d\n", ch, pitch, vel);
}

void pdnoteon2(int ch, int pitch, int vel)
{
  printf("pd2 noteon: %d %d %d\n", ch, pitch, vel);
}

void pdprint(const char *s)
{
  printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel)
{
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}

void *thread(void *ptr)
{
  int type = (int)ptr;
  printf("Thread - %d\n", type);
  return ptr;
}

uint32_t getTotalHeap(void) {
#if PICO
  extern char __StackLimit, __bss_end__;
  return &__StackLimit  - &__bss_end__;
#else
  return 0;
#endif
}

uint32_t getFreeHeap(void) {
#if PICO
  struct mallinfo m = mallinfo();
  return getTotalHeap() - m.uordblks;
#else
  return 0;
#endif
}
static volatile unsigned int hardfaultcontinue;

void main_task(__unused void *params)
{
  printf("main_task: start\n");

#if PICO
  vTaskDelay(2000);
#endif

  printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  libpd_init();
  // pdmain_init();

  printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  while (1)
  {
#if PICO
    vTaskDelay(2000);
#endif
    printf("main_task: tick.\n");
  }
}

#if PICO
void faultHandlerWithExcFrame(struct CortexExcFrame *exc, uint32_t cause, uint32_t extraData, struct CortexPushedRegs *pushedRegs)
{
	static const char *names[] = {
		[EXC_m0_CAUSE_MEM_READ_ACCESS_FAIL] = "Memory read failed",
		[EXC_m0_CAUSE_MEM_WRITE_ACCESS_FAIL] = "Memory write failed",
		[EXC_m0_CAUSE_DATA_UNALIGNED] = "Data alignment fault",
		[EXC_m0_CAUSE_BAD_CPU_MODE] = "Bad CPU Mode",
		[EXC_m0_CAUSE_CLASSIFIER_ERROR] = "Classifier error",
		[EXC_m0_CAUSE_UNDEFINSTR16] = "Undef 16-bit instr",
		[EXC_m0_CAUSE_UNDEFINSTR32] = "Undef 32-bit instr",
		[EXC_m0_CAUSE_BKPT_HIT] = "Breakpoint hit",
		[EXC_m0_CAUSE_UNCLASSIFIABLE] = "Unclassified fault",
	};
	uint32_t i;

	printf("%s sr = 0x%08x\n", (cause < sizeof(names) / sizeof(*names) && names[cause]) ? names[cause] : "????", exc->sr);
	printf("R0  = 0x%08x  R8  = 0x%08x\n", exc->r0_r3[0], pushedRegs->regs8_11[0]);
	printf("R1  = 0x%08x  R9  = 0x%08x\n", exc->r0_r3[1], pushedRegs->regs8_11[1]);
	printf("R2  = 0x%08x  R10 = 0x%08x\n", exc->r0_r3[2], pushedRegs->regs8_11[2]);
	printf("R3  = 0x%08x  R11 = 0x%08x\n", exc->r0_r3[3], pushedRegs->regs8_11[3]);
	printf("R4  = 0x%08x  R12 = 0x%08x\n", pushedRegs->regs4_7[0], exc->r12);
	printf("R5  = 0x%08x  SP  = 0x%08x\n", pushedRegs->regs4_7[1], (exc + 1));
	printf("R6  = 0x%08x  LR  = 0x%08x\n", pushedRegs->regs4_7[2], exc->lr);
	printf("R7  = 0x%08x  PC  = 0x%08x\n", pushedRegs->regs4_7[3], exc->pc);

	switch (cause) {
		case EXC_m0_CAUSE_MEM_READ_ACCESS_FAIL:
			printf(" -> failed to read 0x%08x\n", extraData);
			break;
		case EXC_m0_CAUSE_MEM_WRITE_ACCESS_FAIL:
			printf(" -> failed to write 0x%08x\n", extraData);
			break;
		case EXC_m0_CAUSE_DATA_UNALIGNED:
			printf(" -> unaligned access to 0x%08x\n", extraData);
			break;
		case EXC_m0_CAUSE_UNDEFINSTR16:
			printf(" -> undef instr16: 0x%04x\n", ((uint16_t*)exc->pc)[0]);
			break;
		case EXC_m0_CAUSE_UNDEFINSTR32:
			printf(" -> undef instr32: 0x%04x 0x%04x\n", ((uint16_t*)exc->pc)[0], ((uint16_t*)exc->pc)[1]);
			break;
	}

	while(1);
}
#endif

int main()
{
#if PICO
  stdio_init_all();
  exception_set_exclusive_handler(HARDFAULT_EXCEPTION, HardFault_Handler);
#endif

  printf("Started.\n");
  printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  char *tmp = malloc(103);
  printf("malloced %X\n", tmp);

#if PICO
  sleep_ms(2000);
#endif

  printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  int srate = 44100;
  libpd_set_verbose(1);
  libpd_set_printhook(pdprint);
  libpd_set_noteonhook(pdnoteon);
  libpd_init();

  tmp = getbytes(100);
  printf("getbytes %X\n", tmp);

  t_float inbuf[64];
  t_float outbuf[64];

  libpd_init_audio(1, 1, srate);

  printf("\n*** before creating initial patch.\n");
  t_binbuf *b = binbuf_new();
  glob_setfilename(0, gensym("main-patch"), gensym("."));
  binbuf_text(b, patchfile, strlen(patchfile));
  binbuf_eval(b, &pd_canvasmaker, 0, 0);

  printf("firing loadbang\n");
  canvas_loadbang((t_canvas *)s__X.s_thing);
  vmess(s__X.s_thing, gensym("pop"), "i", 0);
  glob_setfilename(0, &s_, &s_);
  binbuf_free(b);
  printf("after creating initial patch.\n\n");

  printf("Before benchmark\n");
#if PICO
  uint32_t T0 = time_us_32();
#endif
  for (int i = 0; i < srate / 64; i++) {
    memset(outbuf, 0, 64*sizeof(float));
    libpd_process_float(1, inbuf, outbuf);
  }

#if PICO
  uint32_t T1 = time_us_32();
  printf("generating 1 second of audio in %d hz took %d us \n", srate, T1-T0);
#endif

  for(int k=0; k<64; k+=4) {
      printf("  soundout[%d] = %f\n", k, outbuf[k]);
  }

#if PICO
  vTaskStartScheduler();
#endif
}
