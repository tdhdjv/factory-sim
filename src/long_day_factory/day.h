#pragma once
#include "define.h"

namespace LongDay{
	enum DayOfTheWeek {
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THRUSDAY,
		FRIDAY,
		SATURDAY,
		UNDEF_DAY
	};

	enum Weather {
		SUNNY,
		CLOUDY,
		WINDY,
		RAINING,
		SNOWING,
		HAIL,
		UNDEF_WEATHER
	};

	struct Day {
		DayOfTheWeek dayOfTheWeek;
		Weather weather;
		i64 mood;
		u64 hoursInADay;
		Day();
	};
}
