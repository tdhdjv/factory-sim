#pragma once

#include "backend/sink.h"
#include "backend/source.h"

namespace LongDay {
    template <class In, class Out>
    class Process : Sink<In>, Source<Out> {
    private:  
        std::queue<In> queue;
        u32 capacity;
    public:
        void set_sink(Sink<Out>* sink) {
            this->sink = sink;
        }

        void consume(const In& product) {
            queue.push(product);
        }

    };
}
