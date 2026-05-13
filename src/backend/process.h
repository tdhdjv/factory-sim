#pragma once

#include <iostream>
#include "backend/sink.h"
#include "backend/source.h"
#include <queue>

namespace LongDay {
    template <class In, class Out>
    class Process : public Sink<In>, public Source<Out> , public Stage {
    protected:  
        std::queue<In> queue;
        u32 capacity;
    public:
        Process(u32 capacity):
            capacity(capacity) {}

        b8 consume(const In& product) override {
            if(!can_consume()) return false;
            queue.push(product);
            return true;
        }

        b8 can_consume() override {
            return queue.size() < capacity;
        }

        void print_status() override {
            std::queue<In> copy = queue;
            std::cout << "[";
            while (!copy.empty()) {
                std::cout << copy.front() << ", ";
                copy.pop();
            }
            std::cout << "] -> ";
        }
    };
}
