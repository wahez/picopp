#include "ws2812.h"
#include <hardware/clocks.h>
#include <cstdint>

namespace PicoPP::WS2812
{

	namespace
	{
		constexpr int T1 = 2;
		constexpr int T2 = 5;
		constexpr int T3 = 3;
	}

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
		return Color{.w=0, .b=g(4), .r=g(0), .g=g(2)};
	}

	using namespace PIOPP;

	RGBLed::RGBLed(PIO p, Pin pin) :
		program{1,
			"start",
			out(Location::X, 1)            .side(0) [T3-2],
			jmp(Condition::notX, "do zero").side(1) [T1-1],
			"do one",
			jmp(Condition::Always, "start").side(1) [T2-1],
			"do zero",
			nop                            .side(0) [T2-1]
		},
		run{
			RunConfig{
				.pio=p,
				.sideset_pins{.base_pin=pin, .num_pins=1},
				.fifo_join = PIO_FIFO_JOIN_TX,
				.out_shift = {
					.right = false,
					.auto_push_pull = true,
					.threshold = 32},
				.freq = 800'000*(T1+T2+T3)
			},
			program}
	{
	}

}
