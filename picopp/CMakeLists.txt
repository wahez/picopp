add_library(picopp
    clock.h
    pins.h
    pio.h
    pio.cc
    pioasm.h
    pioasm.cc
    pwm.h
)

target_link_libraries(picopp
    pico_stdlib
    hardware_pio
    hardware_pwm
)

target_include_directories(picopp INTERFACE ../)
