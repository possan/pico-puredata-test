include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

add_library(libpd STATIC)

# include_directories(libpd PUBLIC src/)

pico_sdk_init()

set (LIBPD_ROOT ${CMAKE_CURRENT_LIST_DIR}/libpd)
set (LWIP_PATH $ENV{PICO_SDK_PATH}/lib/lwip/)
# set (ENV{FREERTOS_KERNEL_PATH} "${CMAKE_SOURCE_DIR}/ext/freertos/FreeRTOS-Kernel")

set(CMAKE_C_FLAGS         "${CMAKE_C_FLAGS} -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -Werror-implicit-function-declaration -Wcast-align -falign-functions=8 -falign-jumps -falign-labels -falign-loops")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -ffast-math -funroll-loops -fomit-frame-pointer -O3 ")
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS} -g -O0")

include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

target_sources(libpd PRIVATE
    # POSIX Compatibility stuff
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_clock.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_mqueue.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_barrier.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_cond.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_mutex.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_semaphore.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_timer.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_unistd.c
    # ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_utils.c

    # PD Code
    ${LIBPD_ROOT}/pure-data/src/d_arithmetic.c
    ${LIBPD_ROOT}/pure-data/src/d_array.c
    ${LIBPD_ROOT}/pure-data/src/d_ctl.c
    ${LIBPD_ROOT}/pure-data/src/d_dac.c
    ${LIBPD_ROOT}/pure-data/src/d_delay.c
    ${LIBPD_ROOT}/pure-data/src/d_fft.c
    ${LIBPD_ROOT}/pure-data/src/d_fft_fftsg.c
    ${LIBPD_ROOT}/pure-data/src/d_filter.c
    ${LIBPD_ROOT}/pure-data/src/d_global.c
    ${LIBPD_ROOT}/pure-data/src/d_math.c
    ${LIBPD_ROOT}/pure-data/src/d_misc.c
    ${LIBPD_ROOT}/pure-data/src/d_osc.c
    ${LIBPD_ROOT}/pure-data/src/d_resample.c
    ${LIBPD_ROOT}/pure-data/src/d_soundfile_aiff.c
    ${LIBPD_ROOT}/pure-data/src/d_soundfile_caf.c
    ${LIBPD_ROOT}/pure-data/src/d_soundfile_next.c
    ${LIBPD_ROOT}/pure-data/src/d_soundfile_wave.c
    ${LIBPD_ROOT}/pure-data/src/d_soundfile.c
    ${LIBPD_ROOT}/pure-data/src/d_ugen.c

    ${LIBPD_ROOT}/pure-data/src/g_all_guis.c
    ${LIBPD_ROOT}/pure-data/src/g_array.c
    ${LIBPD_ROOT}/pure-data/src/g_bang.c
    ${LIBPD_ROOT}/pure-data/src/g_canvas.c
    ${LIBPD_ROOT}/pure-data/src/g_clone.c
    ${LIBPD_ROOT}/pure-data/src/g_editor_extras.c
    ${LIBPD_ROOT}/pure-data/src/g_editor.c
    ${LIBPD_ROOT}/pure-data/src/g_graph.c
    ${LIBPD_ROOT}/pure-data/src/g_guiconnect.c
    ${LIBPD_ROOT}/pure-data/src/g_io.c
    ${LIBPD_ROOT}/pure-data/src/g_mycanvas.c
    ${LIBPD_ROOT}/pure-data/src/g_numbox.c
    ${LIBPD_ROOT}/pure-data/src/g_radio.c
    ${LIBPD_ROOT}/pure-data/src/g_readwrite.c
    ${LIBPD_ROOT}/pure-data/src/g_rtext.c
    ${LIBPD_ROOT}/pure-data/src/g_scalar.c
    ${LIBPD_ROOT}/pure-data/src/g_slider.c
    ${LIBPD_ROOT}/pure-data/src/g_template.c
    ${LIBPD_ROOT}/pure-data/src/g_text.c
    ${LIBPD_ROOT}/pure-data/src/g_toggle.c
    ${LIBPD_ROOT}/pure-data/src/g_traversal.c
    ${LIBPD_ROOT}/pure-data/src/g_undo.c
    ${LIBPD_ROOT}/pure-data/src/g_vumeter.c

    ${LIBPD_ROOT}/pure-data/src/m_atom.c
    ${LIBPD_ROOT}/pure-data/src/m_binbuf.c
    ${LIBPD_ROOT}/pure-data/src/m_class.c
    ${LIBPD_ROOT}/pure-data/src/m_conf.c
    ${LIBPD_ROOT}/pure-data/src/m_glob.c
    ${LIBPD_ROOT}/pure-data/src/m_memory.c
    ${LIBPD_ROOT}/pure-data/src/m_obj.c
    ${LIBPD_ROOT}/pure-data/src/m_pd.c
    ${LIBPD_ROOT}/pure-data/src/m_sched.c

    ${LIBPD_ROOT}/pure-data/src/s_audio.c
    ${LIBPD_ROOT}/pure-data/src/s_audio_dummy.c
    ${LIBPD_ROOT}/pure-data/src/s_loader.c
    ${LIBPD_ROOT}/pure-data/src/s_main.c
    ${LIBPD_ROOT}/pure-data/src/s_net.c
    ${LIBPD_ROOT}/pure-data/src/s_path.c
    ${LIBPD_ROOT}/pure-data/src/s_print.c
    ${LIBPD_ROOT}/pure-data/src/s_utf8.c
    ${LIBPD_ROOT}/pure-data/src/s_inter_gui.c
    ${LIBPD_ROOT}/pure-data/src/s_inter.c

    ${LIBPD_ROOT}/pure-data/src/x_acoustics.c
    ${LIBPD_ROOT}/pure-data/src/x_arithmetic.c
    ${LIBPD_ROOT}/pure-data/src/x_array.c
    ${LIBPD_ROOT}/pure-data/src/x_connective.c
    ${LIBPD_ROOT}/pure-data/src/x_file.c
    ${LIBPD_ROOT}/pure-data/src/x_gui.c
    ${LIBPD_ROOT}/pure-data/src/x_interface.c
    ${LIBPD_ROOT}/pure-data/src/x_list.c
    ${LIBPD_ROOT}/pure-data/src/x_midi.c
    ${LIBPD_ROOT}/pure-data/src/x_misc.c
    # ${LIBPD_ROOT}/pure-data/src/x_net.c
    ${LIBPD_ROOT}/pure-data/src/x_scalar.c
    ${LIBPD_ROOT}/pure-data/src/x_text.c
    ${LIBPD_ROOT}/pure-data/src/x_time.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp_fun.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp_if.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp.c

    # Some extras
    ${LIBPD_ROOT}/pure-data/extra/bob~/bob~.c
    ${LIBPD_ROOT}/pure-data/extra/bonk~/bonk~.c
    ${LIBPD_ROOT}/pure-data/extra/choice/choice.c
    ${LIBPD_ROOT}/pure-data/extra/fiddle~/fiddle~.c
    ${LIBPD_ROOT}/pure-data/extra/loop~/loop~.c
    ${LIBPD_ROOT}/pure-data/extra/lrshift~/lrshift~.c
    # ${LIBPD_ROOT}/pure-data/extra/pd~/pd~.c
    # ${LIBPD_ROOT}/pure-data/extra/pd~/pdsched~.c
    ${LIBPD_ROOT}/pure-data/extra/pique/pique.c
    ${LIBPD_ROOT}/pure-data/extra/sigmund~/sigmund~.c
    ${LIBPD_ROOT}/pure-data/extra/stdout/stdout.c

    # LibPD Wrapper
    ${LIBPD_ROOT}/libpd_wrapper/z_hooks.c
    ${LIBPD_ROOT}/libpd_wrapper/z_libpd.c
    ${LIBPD_ROOT}/libpd_wrapper/x_libpdreceive.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_print_util.c
    
    ${LIBPD_ROOT}/libpd_wrapper/s_libpdmidi.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_queued.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_ringbuffer.c

    # Stubs
    ${CMAKE_CURRENT_LIST_DIR}/src/stubs/gui.c

    ${CMAKE_CURRENT_LIST_DIR}/src/lib.c
)

include_directories(libpd PRIVATE


$ENV{CONFIG_PATH}

${CMAKE_CURRENT_LIST_DIR}/include
    ${LWIP_PATH}/src/include
    ${LWIP_PATH}/src/include/compat/posix
    ${LWIP_PATH}/contrib/ports/unix/port/include

    ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/include
    ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/include/portable
    ${FREERTOS_POSIX_ROOT}/FreeRTOS-Plus-POSIX/include/portable/pc/windows

    ${LIBPD_ROOT}/pure-data/src
    ${LIBPD_ROOT}/libpd_wrapper
    ${LIBPD_ROOT}/libpd_wrapper/util
)

target_include_directories(libpd INTERFACE
    ${LIBPD_ROOT}/pure-data/src
    ${LIBPD_ROOT}/libpd_wrapper
    ${LIBPD_ROOT}/libpd_wrapper/util
)

target_link_libraries(libpd
    pico_base_headers
    pico_stdlib
    pico_malloc
    pico_mem_ops

    FreeRTOS-Kernel-Heap4
    freertos-posix
)

target_compile_options(libpd PRIVATE
    "-D_POSIX_THREADS"

    # Also defined by espd
    "-DPD"
    "-DPD_INTERNAL"
    "-DPD_HEADLESS"
    "-DSTUPID_SORT"
    "-DSYMTABHASHSIZE=512"
    "-DHAVE_UNISTD_H"
    "-DHAVE_ALLOCA_H"

    # PD Extra stuff
    "-UPDINSTANCE"
    "-DUSEAPI_DUMMY"
    # "-DLOUD"
    "-DLIBPD_EXTRA"

    # My hacky stuff
    "-DPICO"
    "-DNONET"

    "-DPDTHREADS=0"
    "-DLWIP"
    "-DLWIP_COMPAT_SOCKETS=2"
    "-DHAVE_MACHINE_ENDIAN_H"
)


set(PICO_SDK_PATH ${PICO_SDK_PATH} CACHE PATH "Path to the Raspberry Pi Pico SDK" FORCE)
include(${PICO_SDK_INIT_CMAKE_FILE})
