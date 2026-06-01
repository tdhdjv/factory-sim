#include "day_time_dilator.h"

namespace LongDay {
	DayTimeDilator::DayTimeDilator(): Machine<Day, Day>(20, 5, 0.02f) {};
	const char* DayTimeDilator::get_name() const {
		return "Day Time Dilator";
	}

	Day DayTimeDilator::transform(const Day& day) {
		Day result = day;
		result.hoursInADay *= 100;
		return result;
	}
}
