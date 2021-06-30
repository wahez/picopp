#include "pio.h"
#include <hardware/clocks.h>


namespace PicoPP::PIOPP
{


	Run::Run(const RunConfig& config, const Program& program) :
		program(program),
		pio(config.pio),
		sm(pio_claim_unused_sm(config.pio, true)),
		offset(pio_add_program(config.pio, &program.program))
	{
		auto config_pins = [&](const PinRange& pins, bool is_out)
		{
			if (pins.num_pins == 0)
				return;
			for (uint i = 0; i < pins.num_pins; ++i)
				pio_gpio_init(config.pio, pins.base_pin + i);
			pio_sm_set_consecutive_pindirs(config.pio, sm, pins.base_pin, pins.num_pins, is_out);
		};
		config_pins(config.in_pins, false);
		config_pins(config.out_pins, true);
		config_pins(config.set_pins, true);
		config_pins(config.sideset_pins, true);
		auto sm_conf = pio_get_default_sm_config();
		sm_config_set_wrap(&sm_conf, offset, offset + program.instructions.size());
		sm_config_set_in_pins(&sm_conf, config.in_pins.base_pin);
		sm_config_set_out_pins(&sm_conf, config.out_pins.base_pin, config.out_pins.num_pins);
		sm_config_set_set_pins(&sm_conf, config.set_pins.base_pin, config.set_pins.num_pins);
		sm_config_set_sideset_pins(&sm_conf, config.sideset_pins.base_pin);
		sm_config_set_sideset(&sm_conf, config.sideset_pins.num_pins, false, false);
		sm_config_set_in_shift(&sm_conf, config.in_shift.right, config.in_shift.auto_push_pull, config.in_shift.threshold);
		sm_config_set_out_shift(&sm_conf, config.out_shift.right, config.out_shift.auto_push_pull, config.out_shift.threshold);
		sm_config_set_fifo_join(&sm_conf, config.fifo_join);
		sm_config_set_clkdiv(&sm_conf, clock_get_hz(clk_sys) / config.freq);
		sm_config_set_jmp_pin(&sm_conf, config.jump_pin);
		pio_sm_init(config.pio, sm, offset, &sm_conf);
		pio_sm_set_enabled(config.pio, sm, true);
	}


	Run::~Run()
	{
		pio_sm_set_enabled(pio, sm, false);
		pio_sm_unclaim(pio, sm);
		pio_remove_program(pio, &program.program, offset);
	}


}
