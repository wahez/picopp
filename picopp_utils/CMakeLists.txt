add_library(picopp_utils
    distance_sensor.h
    distance_sensor.cc
    led.h
    meter.h
    ws2812.h
    ws2812.cc
)

target_compile_options(picopp_utils PRIVATE -Wall -Werror)

target_link_libraries(picopp_utils picopp pico_stdlib)
