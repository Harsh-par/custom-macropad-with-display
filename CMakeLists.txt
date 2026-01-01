#Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Initialise pico_sdk from installed location
#(note this can come from environment, CMake cache etc)

#== DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0-a4)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
#====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

#Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(rpp_macropad C CXX ASM)

#Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

# Important
add_executable(rpp_macropad 
        src/rpp_macropad.c
        src/usb_descriptors.c 
        src/encoder.c
        src/keys.c  
        src/gc9a01.c
        src/st7789.c
        src/gui.c
        src/bitmaps.c
        src/backlight.c
        src/actions.c
        )

# Important
target_include_directories(rpp_macropad PRIVATE src) 
target_include_directories(rpp_macropad PRIVATE include) 

pico_set_program_name(rpp_macropad "rpp_macropad")
pico_set_program_version(rpp_macropad "0.1")

#Generate PIO header
pico_generate_pio_header(rpp_macropad ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

#Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(rpp_macropad 1)
pico_enable_stdio_usb(rpp_macropad 0)

# Important
target_link_libraries(rpp_macropad
        pico_stdlib
        pico_multicore
        tinyusb_device
        tinyusb_board
        )

# Add the standard include files to the build
target_include_directories(rpp_macropad PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )

# Add any user requested libraries
target_link_libraries(rpp_macropad 
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
        hardware_pwm
        )

pico_add_extra_outputs(rpp_macropad)
