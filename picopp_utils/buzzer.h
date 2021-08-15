#pragma once
#include <picopp/pwm.h>
#include <hardware/clocks.h>


namespace PicoPP::PWM {


class Buzzer
{
public:
	class Slice
	{
	public:
		Slice(const Slice&)	= delete;
		explicit Slice(uint s) :
			slice(s, 255, 440)
		{}
	private:
		friend class Buzzer;
		PWM::Slice slice;
	};

	Buzzer(const Buzzer&) = delete;
	explicit Buzzer(Pin p, Slice& slice);

	void play(float freq)
	{
		const auto wrap = clock_get_hz(clk_sys) / (255 * freq);
		slice.set_wrap(wrap);
		pin.set(wrap / 2);
	}

	void off()
	{
		pin.set(0);
	}

private:
	PWM::Slice& slice;
	PWM::Out pin;
};


}
