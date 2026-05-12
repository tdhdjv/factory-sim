#pragma once
#include "backend/sink.h"

namespace LongDay {
    //Interface
    template <class T>
    class Source {
    Sink<T>* consumer;
    public:
        virtual void feed() = 0;
    };
}
