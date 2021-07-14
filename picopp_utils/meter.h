#pragma once
#include <picopp/pins.h>
#include <vector>


namespace PicoPP {


struct Meter // this class works very nice with the maker pi pico because it has leds for every pin out of the box
{
	struct Range
	{
		int min=0;
		int max=255;
	};

	Meter(std::initializer_list<Out*> ls) :
		leds{ls}
	{}

	void set(int value, Range range={0,255})
	{
		range.max = std::max(range.min+1, range.max);
		const uint num_leds = leds.size() * (value-range.min)/(range.max-range.min);
		for (uint i = 0; i < leds.size(); i++)
			leds[i]->set(i < num_leds);
	}

private:
	std::vector<Out*> leds;
};


}
