#include "define.h"

namespace LongDay {

	enum DayOfWeek {
		SUNDAY,
		MONDAY,
		TUESDAY,
		WEDNESDAY,
		THURSDAY,
		FRIDAY,
		SATURDAY,
	};

	enum DayWeather {
		SUNNY,
		WINDY,
		RAIN,
		OVERCAST,
		SNOW,
	};

	struct Day {
		DayOfWeek dayOfWeek;
		DayWeather weather;

		u32 year;
		u8 month;
		u8 day;

		u32 workHours;
		//The amount of seconds in a day
		u64 hourPerDay;
	};
}
