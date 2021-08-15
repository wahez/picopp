#pragma once
#include <string_view>


namespace PicoPP::PWM {


// for instance "a#3"
float note_to_freq(std::string_view note);

float operator"" _note(const char*, std::size_t);


}
