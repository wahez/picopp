add_library(picopp_utils
    ws2812.h
    ws2812.cc
)

target_compile_options(picopp_utils PRIVATE -Wall -Werror)

target_link_libraries(picopp_utils picopp pico_stdlib)
