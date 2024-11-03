include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(freertos-posix)

add_library(freertos-posix STATIC)

# include_directories(freertos-plus-posix PUBLIC src/)
set(POSIX_PATH "$ENV{FREERTOS_POSIX_PATH}/Lab-Project-FreeRTOS-POSIX/FreeRTOS-Plus-POSIX")
set(LAB_PATH "$ENV{FREERTOS_POSIX_PATH}/Lab-Project-FreeRTOS-POSIX")
# set (LIBPD_ROOT ${CMAKE_CURRENT_LIST_DIR}/libpd)
# set (ENV{FREERTOS_KERNEL_PATH} "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel")

pico_sdk_init()

include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# /FreeRTOS-Plus-POSIX
# include($ENV{FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

target_sources(freertos-posix PRIVATE
    ${POSIX_PATH}/source/FreeRTOS_POSIX_clock.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_mqueue.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_semaphore.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_timer.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_pthread_barrier.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_pthread_cond.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_pthread_mutex.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_pthread.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_unistd.c
    ${POSIX_PATH}/source/FreeRTOS_POSIX_utils.c
)

include_directories(freertos-posix PRIVATE
    # ${CMAKE_CURRENT_LIST_DIR}/include
    # ${FREERTOS_POSIX_PATH}/../include/FreeRTOS_POSIX
    # ${FREERTOS_POSIX_PATH}/include/portable/pc/windows
    # ${FREERTOS_POSIX_PATH}/include
    # ${FREERTOS_POSIX_PATH}/include/portable
    # ${FREERTOS_POSIX_PATH}../../port
    # ${FREERTOS_POSIX_PATH}/../include/private
    # ${FREERTOS_POSIX_PATH}/../include
    # ${FREERTOS_POSIX_PATH}/../include/FreeRTOS_POSIX

    $ENV{CONFIG_PATH}

    $ENV{FREERTOS_POSIX_PATH}/port

    ${LAB_PATH}/include
    ${LAB_PATH}/include/private
    ${LAB_PATH}/FreeRTOS-Plus-POSIX/include
    ${LAB_PATH}/FreeRTOS-Plus-POSIX/include/portable
)

target_include_directories(freertos-posix INTERFACE
    # ${FREERTOS_POSIX_PATH}/port
    # ${LAB_PATH}/include
    # ${LAB_PATH}/include/private
    # ${LAB_PATH}/FreeRTOS-Plus-POSIX/include
    # ${LAB_PATH}/FreeRTOS-Plus-POSIX/include/portable

    # ${FREERTOS_POSIX_PATH}/../include
    # ${CMAKE_CURRENT_LIST_DIR}/include
    # ${FREERTOS_POSIX_PATH}/include/portable/pc/windows
)

target_link_libraries(freertos-posix
    pico_base_headers
    pico_stdlib
    FreeRTOS-Kernel
    # FreeRTOS-Kernel-Heap4
)

# add_compile_options(
#     "-DPD"
#     "-DPD_INTERNAL"
#     "-DPICO"
#     "-DNONET"
#     "-DLWIP"
#     "-DUSEAPI_DUMMY"
#     "-DHAVE_UNISTD_H"
#     "-DHAVE_ALLOCA_H"
#     "-DHAVE_MACHINE_ENDIAN_H"
#     "-DLIBPD_EXTRA"
# )

# set(PICO_SDK_PATH ${PICO_SDK_PATH} CACHE PATH "Path to the Raspberry Pi Pico SDK" FORCE)
# include(${PICO_SDK_INIT_CMAKE_FILE})

# # include(${LIBPD_ROOT}/CMakeLists.txt)

# # add_subdirectory(${PI_PATH}/${FREERTOS_KERNEL_RP2040_RELATIVE_PATH} FREERTOS_KERNEL)
