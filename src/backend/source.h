#pragma once
#include "backend/sink.h"
#include "backend/stage.h"

namespace LongDay {
    //Interface
    template <class T>
    class Source {
    protected:
        Sink<T>* consumer;
        virtual b8 feed() = 0;
    public:
        void set_consumer(Sink<T>* consumer) {
            this->consumer = consumer;
        }
    };
}
