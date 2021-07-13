#pragma once
#include <picopp/picopp.h>
#include <picopp/pwm.h>
#include <hardware/clocks.h>
#include <hardware/pwm.h>


namespace PicoPP::PWM {


	class Servo
	{
	public:
		class Slice
		{
		public:
			Slice(const Slice&)	= delete;
			explicit Slice(uint s) :
				slice(s, float(clock_get_hz(clk_sys)) / (50*5120), 10485)
			{
				const auto div = float(clock_get_hz(clk_sys)) / (50 * 5120);
				slice.set_div(div);
			}
		private:
			friend class Servo;
			PWM::Slice slice;
		};

		Servo(const Servo&) = delete;

		explicit Servo(Pin p, Slice& s) :
			pin(s.slice, p)
		{
			set(127);
		}

		void set(std::uint8_t point)
		{
			pin.set(524 + 2 * point);
		}

	private:
		Out pin;
	};


}
