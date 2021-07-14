#include <picopp/clock.h>
#include <picopp_utils/ws2812.h>


int main()
{
	using namespace std::literals;
	using namespace PicoPP;
	using namespace PicoPP::WS2812;
	auto led = PicoPP::WS2812::RGBLed(pio0, 28);
	led.put_blocking("ffffff"_rgb);  // White
	for (auto i = 0; i < 256; ++i)
	{
		led.put_blocking(rgb(i, i, i));
		sleep_for(10ms);
	}
	led.put_blocking("ffffff"_rgb);  // White
	sleep_for(1000ms);
	led.put_blocking("ff0000"_rgb);  // Red
	sleep_for(1500ms);
	led.put_blocking("00ff00"_rgb);  // Green
	sleep_for(1500ms);
	led.put_blocking("0000ff"_rgb);  // Blue
	sleep_for(1500ms);
	led.put_blocking("ffff00"_rgb);
	sleep_for(1500ms);
	led.put_blocking("00ffff"_rgb);
	sleep_for(1500ms);
	led.put_blocking("ff00ff"_rgb);
	sleep_for(1500ms);
	led.put_blocking("000000"_rgb);  // Black or off
	sleep_for(1500ms);

	sleep_for(1000ms);
	for (int i = 0; i <= 60; i++) {
	  led.put_blocking("000000"_rgb);  // Black or off
	}

	sleep_for(1000ms);
}

