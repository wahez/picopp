#include <picopp_utils/led.h>
#include <array>


using Led = PicoPP::PWM::Led;


struct MakerPiPico
{
	Led::Slice slice0{0};
	Led::Slice slice1{1};
	Led::Slice slice2{2};
	Led::Slice slice3{3};
	Led::Slice slice4{4};
	Led::Slice slice5{5};
	Led::Slice slice6{6};
	Led::Slice slice7{7};
	Led led0{0, slice0};
	Led led1{1, slice0};
	Led led2{2, slice1};
	Led led3{3, slice1};
	Led led4{4, slice2};
	Led led5{5, slice2};
	Led led6{6, slice3};
	Led led7{7, slice3};
	Led led8{8, slice4};
	Led led9{9, slice4};
	Led led10{10, slice5};
	Led led11{11, slice5};
	Led led12{12, slice6};
	Led led13{13, slice6};
	Led led14{14, slice7};
	Led led15{15, slice7};
};


int main()
{
	auto pico = MakerPiPico{};
	auto leds = std::array{
		&pico.led15,
		&pico.led14,
		&pico.led13,
		&pico.led12,
		&pico.led11,
		&pico.led10,
		&pico.led9,
		&pico.led8,
		&pico.led7,
		&pico.led6,
		&pico.led5,
		&pico.led4,
		&pico.led3,
		&pico.led2,
		&pico.led1,
		&pico.led0};

	const auto speed = 1;
	for (uint step = 0;; step += speed)
	{
		if (step > 255)
			step -= 255;
		for (auto l = 0u; l < leds.size(); ++l)
		{
			int phase = step + l * 256/leds.size(); // this assumes that 256 divides by the number of leds
			if (phase > 255)
				phase -= 255;
			const std::uint8_t intensity = (phase-127)*(phase-128)/64;
			leds[l]->set_intensity(intensity);
		}
		PicoPP::sleep_for(10ms);
	}
}
