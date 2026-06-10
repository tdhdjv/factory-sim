#include "day_time_dilator.h"
#include <iostream>

namespace LongDay {
	DayTimeDilator::DayTimeDilator(f32 breakDownProbability): Machine<Day, Day>(20, 5, breakDownProbability) {};
	const char* DayTimeDilator::get_name() const {
		return "Day Time Dilator";
	}

	Day DayTimeDilator::transform(const Day& day) {
		Day result = day;
		result.hoursInADay *= 100;
		return result;
	}

}
