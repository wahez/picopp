#pragma once
#include <chrono>
#include <hardware/timer.h>
#include <pico/time.h>


namespace PicoPP {


struct Clock
{
	using duration = std::chrono::microseconds;
	using rep = duration::rep;
	using period = duration::period;
	using time_point = std::chrono::time_point<Clock, duration>;
	static const bool is_steady = true;

	static time_point now() { return time_point{duration{time_us_64()}}; }
};


inline void sleep_for(std::chrono::microseconds us) { using namespace std::literals; sleep_us(us/1us); }
inline void sleep_until(Clock::time_point time)
{
	using namespace std::literals;
	absolute_time_t t;
	update_us_since_boot(&t, time.time_since_epoch()/1us);
	::sleep_until(t);
}

}
