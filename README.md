# picopp

Some examples of programming a Raspberry Pi Pico using C++.

## Directory structure
- picopp: C++ wrappers for the C-sdk. This makes the C-api a bit more convenient in a typical C++ program. Also includes a way to write pio asm directly in C++.
- picopp_utils: Some example classes that can be reused and that use the C++ api wrappers.
- examples: some example programs that use the two libraries above. Most of these were written for a Pico plugged in to a maker pi pico board. But they can be useful in other setups as well.

## PIO ASM in C++
I looked at the example PIO code to drive a WS2812 RGB LED. The integration with CMake works really well, but I wanted to understand it a bit better. Also I would prefer to see all the code in one file. So I created a way to write the assembly in C++. I should support almost all the features that the regular assembler supports. Look at picopp_utils/ws2812.cc or picopp_utils/distance_sensor.cc for examples.
