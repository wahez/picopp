add_library(picopp
    picopp.h
    pio.h
    pio.cc
    pioasm.h
    pioasm.cc
)

target_link_libraries(picopp pico_stdlib hardware_pio)

target_include_directories(picopp INTERFACE ../)
