#include "test.h"
#include <iostream>

namespace LongDay {
    b8 I32Source::feed() {
        this->consumer->consume(10);
        return true;
    };

    void I32Source::tick() {
        feed();
    };

    i32 DoubleMachine::transform(const i32& input) {
        return 2 * input;
    }

    b8 PrintI32Sink::can_consume() {
        return true;
    }

    b8 PrintI32Sink::consume(const i32& value) {
        std::cout << value <<std::endl;
        return true;
    }

    void PrintI32Sink::tick() {}
}
