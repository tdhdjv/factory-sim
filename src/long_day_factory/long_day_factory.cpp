#include "long_day_factory.h"
#include "backend/conveyor.h"
#include "long_day_factory/day.h"
#include "long_day_factory/gloom_and_doom.h"
#include "long_day_factory/hope_and_dream_crusher.h"
#include "long_day_factory/gloom_injector.h"
#include "long_day_factory/day_time_dilator.h"
#include <memory>

namespace LongDay {
	LongDayFactory::LongDayFactory() {
		append(std::make_unique<HopeAndDreamsCrusher>())
		.append(std::make_unique<Conveyor<GloomAndDoom>>(2))
		.append(std::make_unique<GloomInjector>())
		.append(std::make_unique<Conveyor<Day>>(3))
		.append(std::make_unique<DayTimeDilator>());
	}

	const char* LongDayFactory::get_name() const {
		return "Long Day Factory";
	}
}
