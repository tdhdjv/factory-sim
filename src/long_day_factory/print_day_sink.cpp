#include "print_day_sink.h"
#include <iostream>

namespace LongDay {
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
