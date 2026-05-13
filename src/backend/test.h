#pragma once
#include "backend/machine.h"
#include "define.h"

namespace LongDay {
    class I32Source: public Source<i32> {
    public:
        b8 feed() override;
    };

    class SquareMachine: public Machine <i32, i32> {
    public:
        i32 transform(const i32& input) override; 
        SquareMachine(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce) {}
    };

    class DoubleMachine: public Machine<i32, i32> {
    public:
        i32 transform(const i32& input) override; 
        DoubleMachine(i32 capacity, i32 ticksToProduce): Machine(capacity, ticksToProduce) {}
    };

    class PrintI32Sink: public Sink<i32> {
    public:
        b8 can_consume() override;
        b8 consume(const i32& value) override;
    };
}
