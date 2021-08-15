add_executable(buzzer
    main.cc
)

target_compile_options(buzzer PRIVATE -Wall -Werror)

target_link_libraries(buzzer picopp pico_stdlib picopp_utils)
pico_add_extra_outputs(buzzer)
