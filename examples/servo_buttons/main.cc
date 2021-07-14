#include <picopp/clock.h>
#include <picopp_utils/led.h>
#include <picopp_utils/smooth_meter.h>
#include <picopp_utils/servo.h>


using namespace PicoPP;
using namespace PicoPP::PWM;


struct MakerPiPico
{
	Servo::Slice slice0{0};
	Led::Slice slice1{1};
	Led::Slice slice2{2};
	Led::Slice slice3{3};
	Led::Slice slice4{4};
	Led::Slice slice5{5};
	Led::Slice slice6{6};
	Led::Slice slice7{7};
	Servo servo0{0, slice0};
	Servo servo1{1, slice0};
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
	In button20{20};
	In button21{21};
	In button22{22};

	SmoothMeter meter{{
		&led15,
		&led14,
		&led13,
		&led12,
		&led11,
		&led10,
		&led9,
		&led8,
		&led7,
		&led6,
		&led5,
		&led4,
		&led3,
		&led2,
	}};
};

int main()
{
	using namespace std::literals;
	auto pico = MakerPiPico{};
	const auto min = 0;
	const auto max = 255;
	const auto mid = (min + max)/2;
	auto v = mid;
	while (true)
	{
		pico.meter.set(v, {min, max});
		pico.servo0.set(v);
		pico.servo1.set(v);
		if (pico.button21.get())
			v = min;
		else if (pico.button20.get())
		{
			v -= 1;
			if (v < min)
				v = min;
		}
		else if (pico.button22.get())
		{
			v += 1;
			if (v > max)
				v = max;
		}
		sleep_for(5ms);
	}
}
