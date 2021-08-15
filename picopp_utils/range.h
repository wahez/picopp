#pragma once

#include <algorithm>


namespace PicoPP {


template<typename Container>
int ssize(const Container& c) { return static_cast<int>(c.size()); }


struct Range
{
	int min=0;
	int max=255;

	template<typename Int>
	Int scale_to(Int value, Range to_range) const
	{
		const auto mx = std::max(max, min+1);
		return (value - min) * (to_range.max - to_range.min) / (mx - min);
	}
};


}
