#include "long_day_factory.h"
#include "backend/conveyor.h"

namespace LongDay {

	LongDayFactory::LongDayFactory() {
		append(std::make_unique<Conveyor<HopeAndDreams>>(2))
		.append(std::make_unique<HopeAndDreamCrusher>(1, 1))
		.append(std::make_unique<Conveyor<DespairAndMisery>>(2))
		.append(std::make_unique<DespairInjector>(5, 0))
		.append(std::make_unique<Conveyor<Day>>(2))
		.append(std::make_unique<DayEnlongator>(3, 2))
		.append(std::make_unique<Conveyor<Day>>(2));
	}

	const char* LongDayFactory::get_name() const {
		return "long day factory";
	}
}
