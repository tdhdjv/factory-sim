#pragma once
#include "define.h"
#include <queue>

namespace LongDay {
    //Interface
    template <class T>
    class Sink {
    public:
        virtual void consume(T& product) = 0;
    };
}
