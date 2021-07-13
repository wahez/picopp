add_executable(servo_buttons
    main.cc
)

target_compile_options(servo_buttons PRIVATE -Wall -Werror)

target_link_libraries(servo_buttons picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(servo_buttons)
