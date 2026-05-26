#pragma once

#include "backend/machine.h"
#include "backend/factory.h"
#include "define.h"

namespace LongDay {

	class LongDayFactory: public Factory<i32, i32> {
	public:
		LongDayFactory();
		const char* get_name() const override;
	};

    class I32Source: public Source<i32> {
    public:
        b8 feed() override;
    };

    class SquareMachine: public Machine <i32, i32> {
    public:
        i32 transform(const i32& input) override; 
		const char* get_name() const override;
        explicit SquareMachine(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce, 0.5f) {}
    };

    class DoubleMachine: public Machine<i32, i32> {
    public:

        i32 transform(const i32& input) override;
		const char* get_name() const override;
        explicit DoubleMachine(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce, 0.2f) {}
    };

    class PrintI32Sink: public Sink<i32> {
    public:
        b8 can_consume() override;
        b8 consume(const i32& value) override;
    };
}
