#include "distance_sensor.h"
#include "hardware/clocks.h"


namespace PicoPP {


using namespace PIOPP;


DistanceSensor::DistanceSensor(PIO p, Pin trigger, Pin sensor) :
	program{0,
		"trigger",
		set(Destination::X, 0)                              [31],
		mov(Destination::Y, Operation::Invert, Source::X)   [31], // all bits in Y set to 1
		set(Destination::PINS, 0b1)                          [9], // 10us for the trigger (clock tick = 1us)
		set(Destination::PINS, 0b0),
		wait(1, WaitSource::PIN, 0),                              // wait for high
		"wait for low",
		jmp(Condition::Y__, "decremented"),
		jmp(Condition::Always, "trigger")                   [31], // timeout
		"decremented",
		jmp(Condition::PIN, "wait for low"),
		mov(Destination::ISR, Operation::Invert, Source::Y) [31], // we output cycle count which is in units of 2us
		push(0, 1)                                          [31], // push to the RX fifo
		jmp(Condition::Always, "trigger")                   [31],
	},
	run{
		RunConfig{
			.pio=p,
			.in_pins{.base_pin=sensor, .num_pins=1},
			.set_pins{.base_pin=trigger, .num_pins=1},
			.jump_pin=sensor,
			.fifo_join = PIO_FIFO_JOIN_NONE,
			.in_shift = {
				.right = false,
				.auto_push_pull = false,
				.threshold = 32},
			.out_shift = {
				.right = false,
				.auto_push_pull = false,
				.threshold = 32},
			.freq = 1'000'000
		},
		program}
{
}


uint DistanceSensor::get_distance_mm()
{
	constexpr uint speed_of_sound_um_per_us = 343;
	const auto half_delay_us = run.get_blocking();
	const auto single_direction_distance_um = half_delay_us * speed_of_sound_um_per_us;
	if (single_direction_distance_um > 10'000'000)
		return 0;
	return single_direction_distance_um / 1000;
}


}
