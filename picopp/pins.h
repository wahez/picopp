#pragma once
#include "pico/stdlib.h"


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

		bool get() const { return gpio_get(pin); }
		bool button_pressed() const { return !get(); }

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


}
