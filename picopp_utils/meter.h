#pragma once
#include "range.h"
#include <picopp/pins.h>
#include <vector>


namespace PicoPP {


struct Meter // this class works very nice with the maker pi pico because it has leds for every pin out of the box
{
	Meter(std::initializer_list<Out*> ls) :
		leds{ls}
	{}

	void set(int value, Range range={0,255})
	{
		const auto num_leds = range.scale_to(value, {0, ssize(leds)});
		for (int i = 0; i < ssize(leds); i++)
			leds[i]->set(i < num_leds);
	}

private:
	std::vector<Out*> leds;
};


}
