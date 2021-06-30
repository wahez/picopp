#pragma once
#include "pioasm.h"
#include <hardware/pio.h>


namespace PicoPP::PIOPP
{

	struct ShiftConfig
	{
		bool right = false;
		bool auto_push_pull = false;
		uint threshold = 32;
	};

	struct PinRange
	{
		uint base_pin = 0;
		uint num_pins = 0;
	};

	struct RunConfig
	{
		PIO pio = pio0;
		PinRange in_pins{};
		PinRange out_pins{};
		PinRange set_pins{};
		PinRange sideset_pins{};
		uint jump_pin = 0;
		pio_fifo_join fifo_join = PIO_FIFO_JOIN_NONE;
		ShiftConfig in_shift{};
		ShiftConfig out_shift{};
		float freq = 10;
	};


	class Program
	{
	public:
		template<typename... Instructions>
		explicit constexpr Program(
				uint num_sideset_pins,
				Instructions&&... ions) :
			instructions(ProgramBuilder::Build(num_sideset_pins, std::forward<Instructions>(ions)...)),
			program{instructions.data(), static_cast<std::uint8_t>(instructions.size()), -1}
		{
		}

	private:
		friend class Run;
		std::vector<std::uint16_t> instructions;
		pio_program program;
	};


	class Run
	{
	public:
		Run(const Run&) = delete;
		explicit Run(const RunConfig&, const Program&);
		~Run();

		void put_blocking(std::uint32_t value)
		{
			pio_sm_put_blocking(pio, sm, value);
		}

		std::uint32_t get_blocking()
		{
			return pio_sm_get_blocking(pio, sm);
		}

		uint get_sm() const { return sm; }

	private:
		const Program& program;
		PIO pio;
		uint sm;
		uint offset;
	};


}
