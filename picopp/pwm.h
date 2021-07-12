#pragma once
#include <picopp/picopp.h>
#include <hardware/pwm.h>


namespace PicoPP::PWM {


	class Slice
	{
	public:
		Slice(const Slice&)	= delete;
		explicit Slice(uint s, std::uint8_t div, std::uint16_t wrap) :
			slice(s)
		{
			auto config = pwm_get_default_config();
			pwm_config_set_clkdiv_int(&config, div);
			pwm_config_set_wrap(&config, wrap);
			pwm_init(slice, &config, false);
			set_enabled(true);
		}
		~Slice()
		{
			set_enabled(false);
		}

		void set_enabled(bool enable=true) { pwm_set_enabled(slice, enable); }
		void set_div(float div) { pwm_set_clkdiv(slice, div); }
		void set_wrap(std::uint16_t wrap) { pwm_set_wrap(slice, wrap); }
		void set_level(uint channel, std::uint16_t level) { pwm_set_chan_level(slice, channel, level); }
		uint get_slice_num() const { return slice; }

	private:
		const uint slice;
	};


	class Out
	{
	public:
		Out(const Out&) = delete;
		explicit Out(Slice& s, Pin pin):
			slice(s),
			channel(pwm_gpio_to_channel(pin))
		{
			assert(pwm_gpio_to_slice_num(pin) == slice.get_slice_num());
			gpio_set_function(pin, GPIO_FUNC_PWM);
		}

		void set(int level)
		{
			slice.set_level(channel, level);
		}

	private:
		Slice& slice;
		uint channel;
	};


}
