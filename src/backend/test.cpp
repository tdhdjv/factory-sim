#include "test.h"
#include "backend/conveyor.h"
#include <iostream>

namespace LongDay {

	LongDayFactory::LongDayFactory() {
		append(std::make_unique<DoubleMachine>(1, 1))
		.append(std::make_unique<Conveyor<i32>>(5))
		.append(std::make_unique<DoubleMachine>(3, 2))
		.append(std::make_unique<Conveyor<i32>>(2));
	}

    b8 I32Source::feed() {
        this->consumer->consume(10);
        return true;
    };

    i32 DoubleMachine::transform(const i32& input) {
        return 2 * input;
    } 
    
    i32 SquareMachine::transform(const i32& input) {
        return input * input;
    }

    const char* DoubleMachine::get_name() const { 
		return "double machine";
	}

	const char* SquareMachine::get_name() const {
		return "square Machine";
	}

	const char* LongDayFactory::get_name() const {
		return "long day factory";
	}

    b8 PrintI32Sink::can_consume() {
        return true;
    }

    b8 PrintI32Sink::consume(const i32& value) {
        std::cout << value <<std::endl;
        return true;
    }
}
