#pragma once
#include <picopp/picopp.h>
#include <picopp/pwm.h>
#include <hardware/clocks.h>


namespace PicoPP::PWM {


	class Led
	{
	public:
		class Slice
		{
		public:
			Slice(const Slice&)	= delete;
			explicit Slice(uint s) :
				slice(s, clock_get_hz(clk_sys) / (100*255*255), 255*255)
			{}
		private:
			friend class Led;
			PWM::Slice slice;
		};

		Led(const Led&) = delete;

		explicit Led(Pin p, Slice& s) :
			pin(s.slice, p)
		{
			assert(slice.wrap == 255*255);
			pin.set(0);
		}

		void set_intensity(std::uint8_t intensity)
		{
			uint level = intensity;
			pin.set(level*level);
		}

	private:
		Out pin;
	};


}
