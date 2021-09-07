add_executable(light
    main.cc
)

target_compile_options(light PRIVATE -Wall -Werror)

target_link_libraries(light picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(light)
