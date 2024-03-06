# REMEMBER: use cmake .. -DFAMILY=rp2040

cmake_minimum_required(VERSION 3.5)

set(PICO_SDK_PATH ~/pico/pico-sdk)
include(${PICO_SDK_PATH}/lib/tinyusb/hw/bsp/family_support.cmake)
family_get_project_name(PROJECT ${CMAKE_CURRENT_LIST_DIR})
project(${PROJECT})
family_initialize_project(${PROJECT} ${CMAKE_CURRENT_LIST_DIR})

set (MECH_USB_SOURCES
    usb_protocol/src/parser/usb_parse.c
    usb_protocol/src/parser/usb_flags.c
    usb_protocol/src/actions/usb_actions.c
)

set (MECH_USB_INCLUDES
    src/utils/include
    src/main/include
    usb_protocol/include
    usb_protocol/include/parser
    usb_protocol/include/subtopics
    usb_protocol/include/actions
    usb_protocol/util
)

add_executable(${PROJECT})

target_sources(
        ${PROJECT} PUBLIC
        ${MECH_USB_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/main.c
        ${CMAKE_CURRENT_SOURCE_DIR}/src/usb_descriptors.c
)

target_include_directories(
        ${PROJECT} PUBLIC
        ${MECH_USB_INCLUDES}
        ${CMAKE_CURRENT_SOURCE_DIR}
        include
)

target_link_libraries(
        ${PROJECT} PUBLIC
        pico_stdlib
        pico_multicore
        hardware_i2c
        hardware_timer
        hardware_pwm
)

family_configure_device_example(${PROJECT})