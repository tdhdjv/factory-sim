#pragma once
#include "backend/machine.h"
#include "day.h"
#include <iostream>

namespace LongDay {
	class DayTimeDilator: public Machine<Day, Day> {
	public:
		explicit DayTimeDilator(f32 breakDownProbability);
		const char* get_name() const override;
		Day transform(const Day& day) override;
	};
}
