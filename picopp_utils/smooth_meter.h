#pragma once
#include "led.h"
#include <vector>


namespace PicoPP::PWM {


struct SmoothMeter
{
	struct Range
	{
		int min=0;
		int max=255;
	};

	SmoothMeter(std::initializer_list<Led*> ls) :
		leds{ls}
	{}

	void set(int value, Range range={0,255})
	{
		value = (value - range.min) * 255 * leds.size() / (range.max - range.min);
		for (auto* led: leds)
		{
			if (value > 255)
				led->set_intensity(255);
			else if (value < 0)
				led->set_intensity(0);
			else
				led->set_intensity(value);
			value -= 255;
		}
	}

private:
	std::vector<Led*> leds;
};


}
