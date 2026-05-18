#pragma once
#include "backend/sink.h"

namespace LongDay {
    //Interface
    template <class T>
    class Source {
    protected:
        Sink<T>* consumer;
    public:
        virtual b8 feed() = 0;
        void set_consumer(Sink<T>* consumer) {
            this->consumer = consumer;
        }
    };
}
