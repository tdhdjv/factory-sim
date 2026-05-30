#pragma once

#include "backend/machine.h"
#include "backend/factory.h"
#include "product/hope_and_dreams.h"
#include "product/despair_and_misery.h"
#include "product/day.h"
#include "define.h"

namespace LongDay {

	class LongDayFactory: public Factory<i32, i32> {
	public:
		LongDayFactory();
		const char* get_name() const override;
	};

    class HopeAndDreamsSource: public Source<i32> {
    public:
        b8 feed() override;
    };

    class HopeAndDreamCrusher: public Machine <HopeAndDreams, DespairAndMisery> {
    public:
        DespairAndMisery transform(const HopeAndDreams& input) override; 
		const char* get_name() const override;
        explicit HopeAndDreamCrusher(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce, 0.5f) {}
    };

    class DespairInjector: public Machine<DespairAndMisery, Day> {
    public:

        Day transform(const DespairAndMisery& input) override;
		const char* get_name() const override;
        explicit DespairInjector(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce, 0.2f) {}
    };

    class DayEnlongator: public Machine<Day, Day> {
    public:

        Day transform(const Day& input) override;
		const char* get_name() const override;
        explicit DayEnlongator(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce, 0.2f) {}
    };

    class DaySink: public Sink<Day> {
    public:
        b8 can_consume() override;
        b8 consume(const Day& value) override;
    };
}
