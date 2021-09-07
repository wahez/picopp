#include "apa102.h"
#include <cstdint>

namespace PicoPP::APA102
{

	Color operator"" _rgb(const char* s, std::size_t len)
	{
		const auto char_to_hex = [&](const char c)
		{
			if (c <= '9')
				return c - '0';
			if (c <= 'F')
				return c - 'A' + 10;
			return c - 'a' + 10;
		};
		const auto g = [&](int i) -> std::uint8_t
		{
			return (char_to_hex(s[i]) << 4) | char_to_hex(s[i+1]);
		};
		assert(len == 6);
		return Color{g(0), g(2), g(4)};
	}

	using namespace PIOPP;

	LedStrip::LedStrip(PIO p, Pin din_pin, Pin clk_pin, float baud) :
		program{1,
			out(Location::PINS, 1).side(0),
			nop.side(1)
		},
		run{
			PIOPP::RunConfig{
				.pio=p,
				.out_pins{.base_pin=din_pin, .num_pins=1},
				.sideset_pins{.base_pin=clk_pin, .num_pins=1},
				.fifo_join = PIO_FIFO_JOIN_TX,
				.out_shift = {
					.right = false,
					.auto_push_pull = true,
					.threshold = 32},
				.freq = 2*baud
			},
			program}
	{
	}

}
