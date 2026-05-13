#include "test.h"
#include <iostream>

namespace LongDay {
    b8 I32Source::feed() {
        this->consumer->consume(10);
        return true;
    };

    i32 DoubleMachine::transform(const i32& input) {
        return 2 * input;
    }
    const char* DoubleMachine::get_name() const { 
		return "double machine";
	}

    b8 PrintI32Sink::can_consume() {
        return true;
    }

    b8 PrintI32Sink::consume(const i32& value) {
        std::cout << value <<std::endl;
        return true;
    }
}
