#pragma once
#include "backend/factory.h"
#include "day.h"
#include "hope_and_dreams.h"

namespace LongDay {
	class LongDayFactory: public Factory<HopeAndDreams, Day> {
	public:
		LongDayFactory(f32 machineBreakDownProbability);
		const char* get_name() const override;
	};
}

