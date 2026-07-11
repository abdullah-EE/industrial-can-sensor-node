cmake_minimum_required(VERSION 3.20)
project(smart_dc_motor_node C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(smart_dc_motor_node
    src/main.c
    src/adc_processing.c
    src/can_protocol.c
    src/fault_manager.c
    src/motor_control.c
    src/platform_stub.c
)

target_include_directories(smart_dc_motor_node PRIVATE inc)
