#pragma once

#include <iostream>
#include "backend/process.h"
#include <queue>

namespace LongDay {
    class StageBase {
		StageBase* next;
	public:
		virtual void connect(StageBase* next) = 0;
		virtual void tick() = 0;
		virtual const char* get_name() const = 0;
		virtual void print_status() = 0;
    };

    template <class In, class Out>
	class Stage : public Process<In, Out>, public StageBase {
		void connect(StageBase* next) override {
			Sink<Out>* sink = dynamic_cast<Sink<Out>*>(next);
			if(!sink) {
				//TODO: Error for wrong type of connect
				return;
			}
			this->set_consumer(sink);
		}
	};

	//An AtomicStage is a Stage that isn't composed out of other stages
    template <class In, class Out>
	class AtomicStage: public Stage<In, Out> {
    protected:  
        std::queue<In> queue;
        u64 capacity;
    public:
        AtomicStage(u64 capacity):
            capacity(capacity) {}


		u64 get_size() const {return queue.size();}
		u64 get_capacity() const {return capacity;}

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
			std::cout << "(";
			std::cout << this->get_name();
			std::cout << ")";
            std::cout << "[";
            while (!copy.empty()) {
                std::cout << copy.front() << ", ";
                copy.pop();
            }
            std::cout << "] -> ";
        }
	};
}

