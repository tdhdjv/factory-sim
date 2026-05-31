#include "long_day_factory.h"
#include "backend/conveyor.h"
#include "long_day_factory/day.h"
#include "long_day_factory/gloom_and_doom.h"
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

	HopeAndDreamsCrusher::HopeAndDreamsCrusher(): Machine<HopeAndDreams, GloomAndDoom>(10, 2, 0.01f) {}

	const char* HopeAndDreamsCrusher::get_name() const {
		return "Hope and Dreams Crusher";
	}
	
	GloomAndDoom HopeAndDreamsCrusher::transform(const HopeAndDreams& hopeAndDreams) {
		GloomAndDoom result;
		result.gloom = hopeAndDreams.hopefulness * 2;
		result.doom = hopeAndDreams.aspiration * hopeAndDreams.hopefulness / 2 + 100;
		return result;
	}

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

	DayTimeDilator::DayTimeDilator(): Machine<Day, Day>(20, 5, 0.02f) {};
	const char* DayTimeDilator::get_name() const {
		return "Day Time Dilator";
	}

	Day DayTimeDilator::transform(const Day& day) {
		Day result = day;
		result.hoursInADay *= 100;
		return result;
	}

	b8 HopeAndDreamsSource::feed() {
		HopeAndDreams hopeAndDreams = {100, 100};
		consumer->consume(hopeAndDreams);
		return true;
	}

	b8 PrintDaySink::can_consume() {
		return true;
	}

	static const char* day_of_the_week_to_str(DayOfTheWeek dayOfTheWeek) {
		switch (dayOfTheWeek) {
			case SUNDAY:
				return "Sunday";
			break;
			case MONDAY:
				return "Monday";
			break;
			case TUESDAY:
				return "Tuesday";
			break;
			case WEDNESDAY:
				return "Wednesday";
			break;
			case THRUSDAY:
				return "Thrusday";
			break;
			case FRIDAY:
				return "Friday";
			break;
			case SATURDAY:
				return "Saturday";
			break;
			case UNDEF_DAY:
				return "UNKNOWN";
			break;
		}
		return "";
	}

	static const char* weather_to_str(Weather weather) {
		switch (weather) {
			case SUNNY:
				return "Sunny";
			break;
			case CLOUDY:
				return "Cloudy";
			break;
			case WINDY:
				return "Windy";
			break;
			case RAINING:
				return "Raining";
			break;
			case SNOWING:
				return "Snowing";
			break;
			case HAIL:
				return "Hail";
			break;
			case UNDEF_WEATHER:
				return "UNKNOWN";
			break;
		}
		return "";
	}

	b8 PrintDaySink::consume(const Day& day) {
		std::cout << "Day {\n" 
		<< "  DayOfWeek: " << day_of_the_week_to_str(day.dayOfTheWeek) << "\n"
		<< "  Weather: " << weather_to_str(day.weather) << "\n"
		<< "  Hours: " << day.hoursInADay << "\n"
		<< "  Mood: " << day.mood << "\n"
		<< "}"
		<< std::endl;
		return true;
	}
}
