cmake_minimum_required(VERSION 3.5)

set(ENV{CONFIG_PATH} "${CMAKE_SOURCE_DIR}/include")
set(ENV{PICO_SDK_PATH} "${CMAKE_SOURCE_DIR}/../../pico-sdk")
set(ENV{FREERTOS_KERNEL_PATH} "${CMAKE_SOURCE_DIR}/ext/freertos/FreeRTOS-Kernel")
set(ENV{FREERTOS_POSIX_PATH} "${CMAKE_SOURCE_DIR}/ext/freertos-posix")
set(ENV{PD_PATH} "${CMAKE_SOURCE_DIR}/ext/pd")

if(PICO)
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif(PICO)

project(pdtest2)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 23)

if(PICO)
    pico_sdk_init()
endif(PICO)

# https://embedded.fm/blog/2017/3/6/exceptional-code
if(PICO)
    set(CMAKE_C_FLAGS         "${CMAKE_C_FLAGS} -Wno-int-to-pointer-cast -Wno-unused-but-set-variable -Wno-unused-function -Wno-format -Wno-stringop-truncation -Wno-unused-const-variable -Wno-pointer-to-int-cast -Werror-implicit-function-declaration -fno-delete-null-pointer-checks -Wcast-align -falign-functions=4 -falign-jumps=4 -falign-labels=4 -falign-loops=4")
    set(PICOFLAG 1)
else(PICO)
    set(CMAKE_C_FLAGS         "${CMAKE_C_FLAGS} -Wno-int-to-pointer-cast -Wno-unused-but-set-variable -Wno-unused-function -Wno-format -Wno-unused-const-variable -Wno-pointer-to-int-cast -Werror-implicit-function-declaration -fno-delete-null-pointer-checks -Wcast-align")
    set(PICOFLAG 0)
endif(PICO)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -ffast-math -funroll-loops -fomit-frame-pointer -O3 ")
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS} -g -O0")

set (LIBPD_ROOT ${CMAKE_CURRENT_LIST_DIR}/ext/pd/libpd)
set (LWIP_PATH $ENV{PICO_SDK_PATH}/lib/lwip/)

if (PICO)
    include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)
    include($ENV{FREERTOS_POSIX_PATH}/freertos-posix-import.cmake)
endif(PICO)

# include($ENV{PD_PATH}/libpd_import.cmake)

# add_subdirectory(ext/freertos-posix)

add_executable(pdtest2)

# pico_generate_pio_header(pdtest2 ${CMAKE_CURRENT_LIST_DIR}/src/test.pio)
# pico_embed_pt_in_binary(pdtest2 ${CMAKE_CURRENT_LIST_DIR}/pt.json)

# function(pico_add_dis_output TARGET)
#     add_custom_command(TARGET ${TARGET} POST_BUILD
#             COMMAND ${CMAKE_OBJDUMP} -h $<TARGET_FILE:${TARGET}> >$<IF:$<BOOL:$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>>,$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>,$<TARGET_PROPERTY:${TARGET},NAME>>.dis
#             COMMAND ${CMAKE_OBJDUMP} -dS $<TARGET_FILE:${TARGET}> >>$<IF:$<BOOL:$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>>,$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>,$<TARGET_PROPERTY:${TARGET},NAME>>.dis
#             )
# endfunction()

# pico_add_extra_outputs(...)
set (PDSRC 

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

##    ${LIBPD_ROOT}/pure-data/src/g_all_guis.c
    ${LIBPD_ROOT}/pure-data/src/g_array.c
##    ${LIBPD_ROOT}/pure-data/src/g_bang.c
    ${LIBPD_ROOT}/pure-data/src/g_canvas.c
    ${LIBPD_ROOT}/pure-data/src/g_clone.c
##    ${LIBPD_ROOT}/pure-data/src/g_editor_extras.c
##    ${LIBPD_ROOT}/pure-data/src/g_editor.c
    ${LIBPD_ROOT}/pure-data/src/g_graph.c
    ${LIBPD_ROOT}/pure-data/src/g_guiconnect.c
    ${LIBPD_ROOT}/pure-data/src/g_io.c
    # ${LIBPD_ROOT}/pure-data/src/g_mycanvas.c
##    ${LIBPD_ROOT}/pure-data/src/g_numbox.c
##    ${LIBPD_ROOT}/pure-data/src/g_radio.c
    ${LIBPD_ROOT}/pure-data/src/g_readwrite.c
    ${LIBPD_ROOT}/pure-data/src/g_rtext.c
    ${LIBPD_ROOT}/pure-data/src/g_scalar.c
##        ${LIBPD_ROOT}/pure-data/src/g_slider.c
    ${LIBPD_ROOT}/pure-data/src/g_template.c
    ${LIBPD_ROOT}/pure-data/src/g_text.c
##        ${LIBPD_ROOT}/pure-data/src/g_toggle.c
##        ${LIBPD_ROOT}/pure-data/src/g_traversal.c
##    ${LIBPD_ROOT}/pure-data/src/g_undo.c
##        ${LIBPD_ROOT}/pure-data/src/g_vumeter.c

    ${LIBPD_ROOT}/pure-data/src/m_atom.c
    ${LIBPD_ROOT}/pure-data/src/m_binbuf.c
    ${LIBPD_ROOT}/pure-data/src/m_class.c
##    ${LIBPD_ROOT}/pure-data/src/m_conf.c
##    ${LIBPD_ROOT}/pure-data/src/m_glob.c
    ${LIBPD_ROOT}/pure-data/src/m_memory.c
    ${LIBPD_ROOT}/pure-data/src/m_obj.c
    ${LIBPD_ROOT}/pure-data/src/m_pd.c
##    ${LIBPD_ROOT}/pure-data/src/m_sched.c

##    ${LIBPD_ROOT}/pure-data/src/s_audio_dummy.c
##    ${LIBPD_ROOT}/pure-data/src/s_audio.c
    ${LIBPD_ROOT}/pure-data/src/s_inter_gui.c
##    ${LIBPD_ROOT}/pure-data/src/s_inter.c
##    ${LIBPD_ROOT}/pure-data/src/s_loader.c
##    ${LIBPD_ROOT}/pure-data/src/s_main.c
##    ${LIBPD_ROOT}/pure-data/src/s_net.c
##    ${LIBPD_ROOT}/pure-data/src/s_path.c
    ${LIBPD_ROOT}/pure-data/src/s_print.c
    ${LIBPD_ROOT}/pure-data/src/s_utf8.c

    ${LIBPD_ROOT}/pure-data/src/x_acoustics.c
    ${LIBPD_ROOT}/pure-data/src/x_arithmetic.c
    ${LIBPD_ROOT}/pure-data/src/x_array.c
    ${LIBPD_ROOT}/pure-data/src/x_connective.c
##    ${LIBPD_ROOT}/pure-data/src/x_file.c
    ${LIBPD_ROOT}/pure-data/src/x_gui.c
    ${LIBPD_ROOT}/pure-data/src/x_interface.c
    ${LIBPD_ROOT}/pure-data/src/x_list.c
##    ${LIBPD_ROOT}/pure-data/src/x_midi.c
    ${LIBPD_ROOT}/pure-data/src/x_misc.c
    # ${LIBPD_ROOT}/pure-data/src/x_net.c
    ${LIBPD_ROOT}/pure-data/src/x_scalar.c
    ${LIBPD_ROOT}/pure-data/src/x_text.c
    ${LIBPD_ROOT}/pure-data/src/x_time.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp_fun.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp_if.c
    ${LIBPD_ROOT}/pure-data/src/x_vexp.c

    # # Some extras
    # ${LIBPD_ROOT}/pure-data/extra/bob~/bob~.c
    # ${LIBPD_ROOT}/pure-data/extra/bonk~/bonk~.c
    # ${LIBPD_ROOT}/pure-data/extra/choice/choice.c
    # ${LIBPD_ROOT}/pure-data/extra/fiddle~/fiddle~.c
    # ${LIBPD_ROOT}/pure-data/extra/loop~/loop~.c
    # ${LIBPD_ROOT}/pure-data/extra/lrshift~/lrshift~.c
    # # ${LIBPD_ROOT}/pure-data/extra/pd~/pd~.c
    # # ${LIBPD_ROOT}/pure-data/extra/pd~/pdsched~.c
    # ${LIBPD_ROOT}/pure-data/extra/pique/pique.c
    # ${LIBPD_ROOT}/pure-data/extra/sigmund~/sigmund~.c
    # ${LIBPD_ROOT}/pure-data/extra/stdout/stdout.c

    # # LibPD Wrapper
    ${LIBPD_ROOT}/libpd_wrapper/z_hooks.c
    ${LIBPD_ROOT}/libpd_wrapper/z_libpd.c
    ${LIBPD_ROOT}/libpd_wrapper/x_libpdreceive.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_print_util.c
    ${LIBPD_ROOT}/libpd_wrapper/s_libpdmidi.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_queued.c
    ${LIBPD_ROOT}/libpd_wrapper/util/z_ringbuffer.c

)

if(PICO)
    target_sources(pdtest2 PRIVATE
        src/main.c
        src/m0FaultDispatch.c
        src/espd.c
        ${PDSRC}
    )
else(PICO)
    target_sources(pdtest2 PRIVATE
        src/main.c
        src/espd.c
        ${PDSRC}
    )
endif(PICO)

if (PICO)
    add_compile_options(-mfloat-abi=softfp)
    add_compile_options(-DHV_SIMD_NEON -mfloat-abi=softfp)
endif (PICO)

target_compile_options(pdtest2 PRIVATE
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
    "-DDEBUGMEM"
    # "-DLIBPD_EXTRA"

    # My hacky stuff
    "-DPICO=${PICOFLAG}"
    "-DNONET"

    "-DPDTHREADS=0"
    "-DLWIP"
    "-DLWIP_COMPAT_SOCKETS=2"
    "-DHAVE_MACHINE_ENDIAN_H"
)

# include_directories(pdtest2 gen/c)

include_directories(pdtest2
    src

    $ENV{CONFIG_PATH}

    ${LWIP_PATH}/src/include
    ${LWIP_PATH}/src/include/compat/posix
    ${LWIP_PATH}/contrib/ports/unix/port/include

    ${LIBPD_ROOT}/pure-data/src
    ${LIBPD_ROOT}/libpd_wrapper
    ${LIBPD_ROOT}/libpd_wrapper/util
)

if (PICO)
    target_link_libraries(pdtest2 LINK_PUBLIC
        pico_multicore
        pico_stdlib
        pico_malloc
        pico_mem_ops
        hardware_adc
        hardware_flash
        hardware_i2c
        hardware_pio
        hardware_watchdog
        hardware_exception
        FreeRTOS-Kernel
        FreeRTOS-Kernel-Heap4
        freertos-posix
    )
endif (PICO)

if (PICO)
    pico_enable_stdio_usb(pdtest2 1)
    pico_enable_stdio_uart(pdtest2 1)

    pico_add_extra_outputs(pdtest2)
endif (PICO)

# pico_add_library(pico_httpd_content NOFLAG)

# pico_set_lwip_httpd_content(pico_httpd_content INTERFACE
#     ${CMAKE_CURRENT_LIST_DIR}/content/index.shtml
#     ${CMAKE_CURRENT_LIST_DIR}/content/dumresp.html
#     ${CMAKE_CURRENT_LIST_DIR}/content/index.js
#     ${CMAKE_CURRENT_LIST_DIR}/content/test1.gif
#     ${CMAKE_CURRENT_LIST_DIR}/content/anim1234.gif
#     ${CMAKE_CURRENT_LIST_DIR}/content/anim12342.gif
#     ${CMAKE_CURRENT_LIST_DIR}/content/glitch64.gif
# )

