#pragma once
#include "backend/machine.h"
#include "day.h"
#include "hope_and_dreams.h"

namespace LongDay {
	class DayTimeDilator: public Machine<Day, Day> {
	public:
		explicit DayTimeDilator();
		const char* get_name() const override;
		Day transform(const Day& day) override;
	};
}
