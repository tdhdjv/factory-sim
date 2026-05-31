#pragma once
#include "backend/factory.h"
#include "backend/machine.h"
#include "day.h"
#include "hope_and_dreams.h"
#include "gloom_and_doom.h"

namespace LongDay {
	class LongDayFactory: public Factory<HopeAndDreams, Day> {
	public:
		LongDayFactory();
		const char* get_name() const override;
	};

	class HopeAndDreamsCrusher: public Machine<HopeAndDreams, GloomAndDoom> {
	public:
		explicit HopeAndDreamsCrusher();
		const char* get_name() const override; 
		GloomAndDoom transform(const HopeAndDreams& hopeAndDreams) override;
	};

	class GloomInjector: public Machine<GloomAndDoom, Day> {
	public:
		explicit GloomInjector();
		const char* get_name() const override; 
		Day transform(const GloomAndDoom& gloomAndDoom) override;
	};

	class DayTimeDilator: public Machine<Day, Day> {
	public:
		explicit DayTimeDilator();
		const char* get_name() const override;
		Day transform(const Day& day) override;
	};

	class HopeAndDreamsSource: public Source<HopeAndDreams> {
	public:
		b8 feed() override;
	};

	class PrintDaySink: public Sink<Day> {
	public:
		b8 can_consume() override;
		b8 consume(const Day& day) override;
	};
}

