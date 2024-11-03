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
else(PICO)
    set(CMAKE_C_FLAGS         "${CMAKE_C_FLAGS} -Wno-int-to-pointer-cast -Wno-unused-but-set-variable -Wno-unused-function -Wno-format -Wno-unused-const-variable -Wno-pointer-to-int-cast -Werror-implicit-function-declaration -fno-delete-null-pointer-checks -Wcast-align")
endif(PICO)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -ffast-math -funroll-loops -fomit-frame-pointer -O3 ")
set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS} -g -O0")

# set (LIBPD_ROOT ${CMAKE_CURRENT_LIST_DIR}/ext/pd/libpd)
set (PD_ROOT ${CMAKE_CURRENT_LIST_DIR}/ext/pure-data)
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
    ${PD_ROOT}/src/d_arithmetic.c
    ${PD_ROOT}/src/d_array.c
    ${PD_ROOT}/src/d_ctl.c
    ${PD_ROOT}/src/d_dac.c
    ${PD_ROOT}/src/d_delay.c
    ${PD_ROOT}/src/d_fft.c
    ${PD_ROOT}/src/d_fft_fftsg.c
    ${PD_ROOT}/src/d_filter.c
    ${PD_ROOT}/src/d_global.c
    ${PD_ROOT}/src/d_math.c
    ${PD_ROOT}/src/d_misc.c
    ${PD_ROOT}/src/d_osc.c
    ${PD_ROOT}/src/d_resample.c
    ${PD_ROOT}/src/d_soundfile_aiff.c
    ${PD_ROOT}/src/d_soundfile_caf.c
    ${PD_ROOT}/src/d_soundfile_next.c
    ${PD_ROOT}/src/d_soundfile_wave.c
    ${PD_ROOT}/src/d_soundfile.c
    ${PD_ROOT}/src/d_ugen.c

##    ${PD_ROOT}/src/g_all_guis.c
    ${PD_ROOT}/src/g_array.c
##    ${PD_ROOT}/src/g_bang.c
    ${PD_ROOT}/src/g_canvas.c
    ${PD_ROOT}/src/g_clone.c
##    ${PD_ROOT}/src/g_editor_extras.c
##    ${PD_ROOT}/src/g_editor.c
    ${PD_ROOT}/src/g_graph.c
    ${PD_ROOT}/src/g_guiconnect.c
    ${PD_ROOT}/src/g_io.c
    # ${PD_ROOT}/src/g_mycanvas.c
##    ${PD_ROOT}/src/g_numbox.c
##    ${PD_ROOT}/src/g_radio.c
    ${PD_ROOT}/src/g_readwrite.c
    ${PD_ROOT}/src/g_rtext.c
    ${PD_ROOT}/src/g_scalar.c
##        ${PD_ROOT}/src/g_slider.c
    ${PD_ROOT}/src/g_template.c
    ${PD_ROOT}/src/g_text.c
##        ${PD_ROOT}/src/g_toggle.c
##        ${PD_ROOT}/src/g_traversal.c
##    ${PD_ROOT}/src/g_undo.c
##        ${PD_ROOT}/src/g_vumeter.c

    ${PD_ROOT}/src/m_atom.c
    ${PD_ROOT}/src/m_binbuf.c
    ${PD_ROOT}/src/m_class.c
##    ${PD_ROOT}/src/m_conf.c
##    ${PD_ROOT}/src/m_glob.c
    ${PD_ROOT}/src/m_memory.c
    ${PD_ROOT}/src/m_obj.c
    ${PD_ROOT}/src/m_pd.c
##    ${PD_ROOT}/src/m_sched.c

##    ${PD_ROOT}/src/s_audio_dummy.c
##    ${PD_ROOT}/src/s_audio.c
    ${PD_ROOT}/src/s_inter_gui.c
##    ${PD_ROOT}/src/s_inter.c
##    ${PD_ROOT}/src/s_loader.c
##    ${PD_ROOT}/src/s_main.c
##    ${PD_ROOT}/src/s_net.c
##    ${PD_ROOT}/src/s_path.c
    ${PD_ROOT}/src/s_print.c
    ${PD_ROOT}/src/s_utf8.c

    ${PD_ROOT}/src/x_acoustics.c
    ${PD_ROOT}/src/x_arithmetic.c
    ${PD_ROOT}/src/x_array.c
    ${PD_ROOT}/src/x_connective.c
##    ${PD_ROOT}/src/x_file.c
    ${PD_ROOT}/src/x_gui.c
    ${PD_ROOT}/src/x_interface.c
    ${PD_ROOT}/src/x_list.c
##    ${PD_ROOT}/src/x_midi.c
    ${PD_ROOT}/src/x_misc.c
    # ${PD_ROOT}/src/x_net.c
    ${PD_ROOT}/src/x_scalar.c
    ${PD_ROOT}/src/x_text.c
    ${PD_ROOT}/src/x_time.c
    ${PD_ROOT}/src/x_vexp_fun.c
    ${PD_ROOT}/src/x_vexp_if.c
    ${PD_ROOT}/src/x_vexp.c

    # # Some extras
    # ${PD_ROOT}/extra/bob~/bob~.c
    # ${PD_ROOT}/extra/bonk~/bonk~.c
    # ${PD_ROOT}/extra/choice/choice.c
    # ${PD_ROOT}/extra/fiddle~/fiddle~.c
    # ${PD_ROOT}/extra/loop~/loop~.c
    # ${PD_ROOT}/extra/lrshift~/lrshift~.c
    # # ${PD_ROOT}/extra/pd~/pd~.c
    # # ${PD_ROOT}/extra/pd~/pdsched~.c
    # ${PD_ROOT}/extra/pique/pique.c
    # ${PD_ROOT}/extra/sigmund~/sigmund~.c
    # ${PD_ROOT}/extra/stdout/stdout.c

    # # LibPD Wrapper
    # ${LIBPD_ROOT}/libpd_wrapper/z_hooks.c
    # ${LIBPD_ROOT}/libpd_wrapper/z_libpd.c
    # ${LIBPD_ROOT}/libpd_wrapper/x_libpdreceive.c
    # ${LIBPD_ROOT}/libpd_wrapper/util/z_print_util.c
    
    # ${LIBPD_ROOT}/libpd_wrapper/s_libpdmidi.c
    # ${LIBPD_ROOT}/libpd_wrapper/util/z_queued.c
    # ${LIBPD_ROOT}/libpd_wrapper/util/z_ringbuffer.c

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
        src/main-local.c
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
    "-DLIBPD_EXTRA"

    # My hacky stuff
    "-DPICO"
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

    ${PD_ROOT}/src

    ${LIBPD_ROOT}/src
    
    # ${LIBPD_ROOT}/libpd_wrapper
    # ${LIBPD_ROOT}/libpd_wrapper/util
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

