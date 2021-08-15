#include "notes.h"
#include <array>
#include <cmath>
#include <cassert>


namespace PicoPP::PWM {


float note_to_freq(std::string_view sv)
{
	// TODO octave split is at c
	constexpr auto notes = std::array{0, 2, 3, 5, 7, 8, 10};
	assert(sv.size() < 4);
	const auto octave = sv[sv.size()-1] - '0';
	auto note = 12 * (octave - 3);
	if (sv[0] > 'G')
		note += notes[sv[0] - 'a'];
	else
		note += notes[sv[0] - 'A'];
	switch (sv[1])
	{
	case '#':
		note++;
		break;
	case 'b':
		note--;
		break;
	}
	return 440 * std::pow(1.0594630943592953f, note);
}

float operator"" _note(const char* s, std::size_t len)
{
	return note_to_freq(std::string_view{s, len});
}


}
