#pragma once
#include <picopp/pins.h>
#include <picopp/pio.h>

namespace PicoPP::APA102
{


	struct Color
	{
		std::uint32_t to_uint32() const
		{
			// should be a nop
			return (header << 24) | (blue << 16) | (green << 8) | red;
		}
		std::uint8_t red;
		std::uint8_t green;
		std::uint8_t blue;
		std::uint8_t header{0b1111'1111};
	};

	Color operator"" _rgb(const char* s, std::size_t len);

	struct LedStrip
	{
		LedStrip(const LedStrip&) = delete;
		explicit LedStrip(PIO p, Pin din_pin, Pin clk_pin, float baud, int num_leds);

		template<typename Container>
		void set_leds_blocking(Container&& colors)
		{
			run.put_blocking(0x0);
			for (const auto color: colors)
				run.put_blocking(color.to_uint32());
			for (int i = 0; i < num_leds - static_cast<int>(colors.size()); ++i)
				run.put_blocking(Color{0, 0, 0}.to_uint32());
			run.put_blocking(0xff'ff'ff'ff);
		}

	private:
		const int num_leds;
		PIOPP::Program program;
		PIOPP::Run run;
	};


}
