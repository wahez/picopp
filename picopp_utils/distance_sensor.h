#pragma once
#include <picopp/picopp.h>
#include <picopp/pio.h>

namespace PicoPP {


	struct DistanceSensor // this code works with a distance sensor such as the one in the camjam edukit
	{
		DistanceSensor(const DistanceSensor&) = delete;
		explicit DistanceSensor(PIO p, Pin trigger, Pin sensor);

		uint get_distance_mm();

	private:
		PIOPP::Program program;
		PIOPP::Run run;
	};


}
