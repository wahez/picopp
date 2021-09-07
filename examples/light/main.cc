#include <picopp/clock.h>
#include <picopp_utils/apa102.h>
#include <random>

using namespace std::literals;


struct Hardware
{
	static constexpr auto din_pin = 1;
	static constexpr auto clk_pin = 0;
	static constexpr auto baudrate = 10000000.0f;
	PicoPP::APA102::LedStrip leds{pio0, din_pin, clk_pin, baudrate};
	PicoPP::In button20{20};
	PicoPP::In button21{21};
	PicoPP::In button22{22};
} hardware;


int main()
{
	auto generator = std::ranlux24_base{};
	auto distr = std::uniform_int_distribution<std::uint_fast32_t>{1, 16};
	auto colors = std::vector{40, PicoPP::APA102::Color{0, 0, 0}};
	while(true)
	{
		if (hardware.button20.button_pressed())
			for (auto& c: colors)
				c.red = std::min(255u, c.red + distr(generator));
		if (hardware.button21.button_pressed())
			for (auto& c: colors)
				c.green = std::min(255u, c.green + distr(generator));
		if (hardware.button22.button_pressed())
			for (auto& c: colors)
				c.blue = std::min(255u, c.blue + distr(generator));
		hardware.leds.set_leds_blocking(colors);
		PicoPP::sleep_for(1s);
	}
}
