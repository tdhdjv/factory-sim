#include "gloom_injector.h"

namespace LongDay {
	GloomInjector::GloomInjector() :Machine<GloomAndDoom, Day>(5, 1, 0.02f) {}

	const char* GloomInjector::get_name() const {
		return "Gloom Injector";
	} 

	Day GloomInjector::transform(const GloomAndDoom& gloomAndDoom) {
		Day day;
		day.dayOfTheWeek = MONDAY;
		day.weather = RAINING;
		day.mood = -gloomAndDoom.gloom * gloomAndDoom.doom;
		return day;
	}
}
