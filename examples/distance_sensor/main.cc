#include <picopp/clock.h>
#include <picopp_utils/distance_sensor.h>
#include <picopp_utils/meter.h>


using namespace PicoPP;


struct MakerPiPico // the MakerPiPico has a led on every pin by default
{
	Out led0{0};
	Out led1{1};
	Out led2{2};
	Out led3{3};
	Out led4{4};
	Out led5{5};
	Out led6{6};
	Out led7{7};
	Out led8{8};
	Out led9{9};
	Out led10{10};
	Out led11{11};
	Out led12{12};
	Out led13{13};
	Out led14{14};
	Out led15{15};
	Meter meter{{
		&led15,
		&led14,
		&led13,
		&led12,
		&led11,
		&led10,
		&led9,
		&led8,
		&led7,
		&led6,
		&led5,
		&led4,
		&led3,
		&led2,
		&led1,
		&led0,
	}};
	DistanceSensor distance_sensor{pio0, 16, 17};
};


int main()
{
	using namespace std::literals;
	MakerPiPico pico;
	const uint max_distance_mm = 500;
	while (true)
	{
		auto distance_mm = pico.distance_sensor.get_distance_mm();
		pico.meter.set(distance_mm, {0, max_distance_mm});
		sleep_for(10ms);
	}
}
