#include <picopp_utils/buzzer.h>
#include <picopp_utils/notes.h>
#include <picopp/clock.h>


using namespace std::literals;
using namespace PicoPP;
using namespace PicoPP::PWM;


struct MakerPiPico
{
	Buzzer::Slice slice{1};
	Buzzer buzzer{18, slice};
} pico;


struct Note
{
	float freq;
	std::chrono::milliseconds duration;
};


int main()
{
	const auto n = [](std::string_view note_str, int duration)
	{
		return Note{note_to_freq(note_str), duration * 100ms};
	};
	constexpr auto pause = Note{0, 10ms};
	const Note melody[] =
	{
		n("c3", 2), n("d3", 2), n("e3", 2), n("c3", 2), pause,
		n("c3", 2), n("d3", 2), n("e3", 2), n("c3", 2), pause,
		n("e3", 2), n("f3", 2), n("g3", 4), pause,
		n("e3", 2), n("f3", 2), n("g3", 4), pause,
		n("g3", 1), n("a3", 1), n("g3", 1), n("f3", 1), n("e3", 2), n("c3", 2), pause,
		n("g3", 1), n("a3", 1), n("g3", 1), n("f3", 1), n("e3", 2), n("c3", 2), pause,
		n("c3", 2), n("g2", 2), n("c3", 4), pause,
		n("c3", 2), n("g2", 2), n("c3", 4), pause,
	};
	for (const auto& note: melody)
	{
		if (note.freq == 0)
			pico.buzzer.off();
		else
			pico.buzzer.play(note.freq);
		sleep_for(note.duration);
	}
	pico.buzzer.off();
}
