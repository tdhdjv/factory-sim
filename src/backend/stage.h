#pragma once

#include <iostream>
#include "backend/process.h"
#include <queue>

namespace LongDay {
    //Interface
    class StageAbstract {
		StageAbstract* next;
	public:
		virtual void connect(StageAbstract* next) = 0;
		virtual void tick() = 0;
		virtual void print_status() = 0;
    };

    template <class In, class Out>
	class Stage: public Process<In, Out>, public StageAbstract {
    protected:  
        std::queue<In> queue;
        u32 capacity;
    public:
        Stage(u32 capacity):
            capacity(capacity) {}

		void connect(StageAbstract* next) override {
			Sink<Out>* sink = next;
			this->set_consumer(sink);
		}

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

