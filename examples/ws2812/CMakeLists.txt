add_executable(ws2812
    main.cc
)

target_compile_options(ws2812 PRIVATE -Wall -Werror)

target_link_libraries(ws2812 picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(ws2812)
