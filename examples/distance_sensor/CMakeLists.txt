add_executable(distance_sensor
    main.cc
)

target_compile_options(distance_sensor PRIVATE -Wall -Werror)

target_link_libraries(distance_sensor picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(distance_sensor)
