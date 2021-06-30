cmake_minimum_required(VERSION 3.13)

include(pico-sdk/pico_sdk_init.cmake)

project(picopp)

pico_sdk_init()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(picopp)
add_subdirectory(picopp_utils)
add_subdirectory(examples)

#add_custom_command(TARGET <output> POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/<output>.uf2 /media/<user>/RPI-RP2/)
