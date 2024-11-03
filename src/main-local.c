#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

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

#include "espd.h"

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

// void mini_printf(const char *format, ...)
// {
//   va_list args; // Declare a va_list variable to manage the variable arguments

//   // Initialize the va_list 'args' to start at the argument after 'format'
//   va_start(args, format);

//   while (*format) // Loop through the format string
//   {
//     // If a format specifier is encountered
//     if (*format == '%')
//     {
//       format++;
//       if (*format == 'd')
//       {
//         // Fetch the next argument as an integer and print it
//         printf("%d", va_arg(args, int));
//       }
//       else if (*format == 's')
//       {
//         // Fetch the next argument as a string and print it
//         printf("%s", va_arg(args, char *));
//       }
//     }
//     else
//     {
//       // Print regular characters
//       putchar(*format);
//     }
//     format++; // Move to the next character
//   }
//   // Cleanup the va_list 'args' after processing
//   va_end(args);
// }

// struct _dummy
// {
//     t_gobj x_gobj;
//     // t_scalar *x_scalar;     /* scalar "containing" the array */
//     // t_glist *x_glist;       /* containing glist */
//     // t_symbol *x_name;       /* unexpanded name (possibly with leading '$') */
//     // t_symbol *x_realname;   /* expanded name (symbol we're bound to) */
//     // unsigned int  x_usedindsp:1;    /* 1 if some DSP routine is using this */
//     // unsigned int  x_saveit:1;       /* we should save this with parent */
//     // unsigned int  x_savesize:1;     /* save size too */
//     // unsigned int  x_listviewing:1;  /* list view window is open */
//     // unsigned int  x_hidename:1;     /* don't print name above graph */
//     // unsigned int  x_edit:1;         /* we can edit the array */
// };

// #define t_dummy struct _dummy

// void garray_free2(t_dummy *x)
// {
// }

// static void garray_const2(t_dummy *x, t_floatarg g)
// {
// }

// static void garray_bounds2(t_dummy *x, t_floatarg g)
// {
// }

// static void garray_list2(t_dummy *x, t_symbol *s, int argc, t_atom *argv)
// {
// }

uint32_t getTotalHeap(void) {
    return 0;
//    extern char __StackLimit, __bss_end__;
   
//    return &__StackLimit  - &__bss_end__;
}

uint32_t getFreeHeap(void) {
    return 0;
//    struct mallinfo m = mallinfo();

//    return getTotalHeap() - m.uordblks;
}

int main()
{
//   stdio_init_all();
//    exception_set_exclusive_handler(HARDFAULT_EXCEPTION, HardFault_Handler);

  printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());
 // sleep_ms(2000);

  printf("Started.\n");
  // sleep_ms(2000);

    // TaskHandle_t task;
    // xTaskCreate(main_task, "TestMainThread", 16384, NULL, tskIDLE_PRIORITY + 1UL, &task);

  char *tmp = malloc(103);
  printf("malloced %X\n", tmp);

  // sleep_ms(2000);

//  mini_printf("Hello %s, number is %d\n", "World", 42);

  // printf("zz1");

  // t_class *
  //     garray_class = class_new(gensym("array"), 0, (t_method)garray_free2,
  //         sizeof(t_dummy), CLASS_GOBJ, 0);
  //     // class_setwidget(garray_class, &garray_widgetbehavior);
  //     class_addmethod(garray_class, (t_method)garray_const2, gensym("const"),
  //         A_DEFFLOAT, A_NULL);
  //     class_addlist(garray_class, garray_list2);
  //     class_addmethod(garray_class, (t_method)garray_bounds2, gensym("bounds"),
  //         A_FLOAT, A_FLOAT, A_FLOAT, A_FLOAT, A_NULL);

  // printf("zz3");


 printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  // libpd_init();
pdmain_init();

 printf("memory: free heap %ld of %ld\n" ,getFreeHeap(), getTotalHeap());

  // printf("Testing pthreads.\n");
  // pthread_t thread1, thread2;
  // int thr = 1;
  // int thr2 = 2;
  // // start the threads
  // pthread_create(&thread1, NULL, *thread, (void *)thr);
  // pthread_create(&thread2, NULL, *thread, (void *)thr2);
  // // wait for threads to finish
  // pthread_join(thread1, NULL);
  // pthread_join(thread2, NULL);

  // printf("Testing libpd.\n");

  tmp = getbytes(100);
  // printf("getbytes   %X\n", tmp);

  // t_pdinstance *pd1, *pd2;
  // int srate = 48000;
  // float inbuf[64], outbuf[128];  // one input channel, two output channels
  //                                // block size 64, one tick per buffer
  // char *filename = "test.pd", *dirname = ".";

  // accept overrides from the commandline:
  // $ pdtest_multi file.pd ../dir
  //   if (argc > 1) {
  //     filename = argv[1];
  //   }
  //   if (argc > 2) {
  //     dirname = argv[2];
  //   }

  // printf("x1\n");
  // mess_init();

  // printf("sched_init...\n");
  // sched_init();
  // printf("sys_lock...\n");
  // sys_lock();
  // printf("obj_init...\n");
  // obj_init();
  // printf("conf_init...\n");
  // conf_init();
  // printf("glob_init...\n");
  // glob_init();
  // printf("garray_init...\n");
  // garray_init();
  // printf("sys_unlock...\n");
  // sys_unlock();
  // printf("done.\n");

  // printf("x1\n");
  //   // init pd
  //   int srate = 44100;
  //   libpd_set_verbose(1);
  //   libpd_set_printhook(pdprint);
  //   libpd_set_noteonhook(pdnoteon);

  // printf("x1.1\n");

  //   libpd_init();
  // printf("x1.2\n");

  //   libpd_init_audio(1, 2, srate);
  //   float inbuf[64], outbuf[128];  // one input channel, two output channels
  //                                  // block size 64, one tick per buffer

  // printf("x2\n");

  //   // compute audio    [; pd dsp 1(
  //   libpd_start_message(1); // one entry in list
  //   libpd_add_float(1.0f);
  //   libpd_finish_message("pd", "dsp");

  // printf("x3\n");

  //   // open patch       [; pd open file folder(
  //   // if (!libpd_openfile(argv[1], argv[2]))
  //   //   return -1;

  // printf("x4\n");

  //   // now run pd for ten seconds (logical time)
  //   int i;
  //   for (i = 0; i < 10 * srate / 64; i++) {
  //     // fill inbuf here
  //     libpd_process_float(1, inbuf, outbuf);
  //     // use outbuf here
  //   }

  // printf("x5\n");

  //   for (i = 0; i < 10; i++)
  //     printf("%g\n", outbuf[i]);

  // libpd_init();

  // pd1 = libpd_new_instance(); // create an instance
  // pd2 = libpd_new_instance(); // create a second instance
  // printf("%d instances\n", libpd_num_instances());

  // libpd_set_instance(pd1); // talk to first pd instance

  // // set hooks for this instance
  // libpd_set_printhook(libpd_print_concatenator);
  // libpd_set_concatenated_printhook(pdprint1);
  // libpd_set_noteonhook(pdnoteon1);

  // libpd_init_audio(1, 2, srate);
  // // compute audio    [; pd dsp 1(
  // libpd_start_message(1); // one entry in list
  // libpd_add_float(1.0f);
  // libpd_finish_message("pd", "dsp");

  // // open patch       [; pd open file folder(
  // libpd_openfile(filename, dirname);

  // // repeat this all for the second instance
  // libpd_set_instance(pd2);
  // libpd_set_printhook(libpd_print_concatenator);
  // libpd_set_concatenated_printhook(pdprint2);
  // libpd_set_noteonhook(pdnoteon2);
  // libpd_init_audio(1, 2, srate);
  // libpd_start_message(1);
  // libpd_add_float(1.0f);
  // libpd_finish_message("pd", "dsp");
  // libpd_openfile(filename, dirname);

  //   /* the following two messages can be sent without setting the pd instance
  //   and anyhow the symbols are global so they may affect multiple instances.
  //   However, if the messages change anything in the pd instance structure
  //   (DSP state; current time; list of all canvases in our instance) those
  //   changes will apply to the current Pd instance, so the earlier messages,
  //   for instance, were sensitive to which was the current one.

  //   Note also that I'm using the fact that $0 is set to 1003, 1004, ...
  //   as patches are opened, it would be better to open the patches with
  //   settable $1, etc parameters to libpd_openfile().  */

  // // [; pd frequency 480 (
  // libpd_set_instance(pd1);
  // libpd_start_message(1);
  // libpd_add_float(480.0f);
  // libpd_finish_message("frequency", "float");

  // // [; pd frequency -480 (
  // libpd_set_instance(pd2);
  // libpd_start_message(1);
  // libpd_add_float(-480.0f);
  // libpd_finish_message("frequency", "float");

  // // now run pd for 3 ticks
  // int i, j;
  // for (i = 0; i < 3; i++) {

  //   libpd_set_instance(pd1);
  //   libpd_process_float(1, inbuf, outbuf);
  //   printf("instance 1, tick %d:\n", i);
  //   for (j = 0; j < 8; j++) {
  //     printf("%f ", outbuf[j]);
  //   }
  //   printf("... \n");

  //   libpd_set_instance(pd2);
  //   libpd_process_float(1, inbuf, outbuf);
  //   printf("instance 2, tick %d:\n", i);
  //   for (j = 0; j < 8; j++) {
  //     printf("%f ", outbuf[j]);
  //   }
  //   printf("... \n");
  // }

  // libpd_free_instance(pd1);
  // libpd_free_instance(pd2);

  // while (true)
  // {
  //   printf("Idle.\n");
  //   sleep_ms(2000);
  // }

  pdmain_tick();
  pdmain_tick();
  pdmain_tick();

//   vTaskStartScheduler();
}
