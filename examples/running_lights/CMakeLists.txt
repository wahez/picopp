add_executable(running_lights
    main.cc
)

target_compile_options(running_lights PRIVATE -Wall -Werror)

target_link_libraries(running_lights picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(running_lights)
