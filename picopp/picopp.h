#pragma once
#include "pico/stdlib.h"
#include <chrono>


using namespace std::literals;


namespace PicoPP {


	using Pin = uint;


	struct In
	{
		In(const In&) = delete;
		explicit In(Pin p): pin(p)
		{
			gpio_init(pin);
			gpio_set_dir(pin, GPIO_IN);
		}

		bool get() const { return !gpio_get(pin); }

	private:
		Pin pin;
	};


	struct Out
	{
		Out(const Out&) = delete;
		explicit Out(Pin p): pin(p)
		{
			gpio_init(pin);
			gpio_set_dir(pin, GPIO_OUT);
		}

		void set(bool v) { gpio_put(pin, v); }

	private:
		Pin pin;
	};


	inline void sleep_for(std::chrono::microseconds us) { sleep_us(us/1us); }


}
