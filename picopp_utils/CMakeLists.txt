add_library(picopp_utils
    apa102.h
    apa102.cc
    buzzer.h
    buzzer.cc
    distance_sensor.h
    distance_sensor.cc
    led.h
    meter.h
    notes.h
    notes.cc
    range.h
    smooth_meter.h
    servo.h
    ws2812.h
    ws2812.cc
)

target_compile_options(picopp_utils PRIVATE -Wall -Werror)

target_link_libraries(picopp_utils picopp pico_stdlib)
