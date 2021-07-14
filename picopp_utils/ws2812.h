#pragma once
#include <picopp/pins.h>
#include <picopp/pio.h>

namespace PicoPP::WS2812
{


	struct Color
	{
		std::uint8_t w = 0;
		std::uint8_t b;
		std::uint8_t r;
		std::uint8_t g;
	};

	inline Color rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) { return Color{.w=0, .b=b, .r=r, .g=g}; }

	Color operator"" _rgb(const char* s, std::size_t len);

	struct RGBLed
	{
		RGBLed(const RGBLed&) = delete;
		explicit RGBLed(PIO p, Pin pin=28);

		void put_blocking(Color c)
		{
			static_assert(sizeof(Color) == 4);
			run.put_blocking(*reinterpret_cast<std::uint32_t*>(&c));
		}

	private:
		PIOPP::Program program;
		PIOPP::Run run;
	};


}
