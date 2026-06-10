#pragma once

#include "backend/process.h"
#include <queue>
#include <stdexcept>

namespace LongDay {

    class AtomicStageBase {
	protected:
        u64 capacity;
    public:
		AtomicStageBase(u64 capacity)
			:capacity(capacity) {};
        virtual ~AtomicStageBase() = default;
        u64 get_capacity() const { return capacity;};
        virtual u64 get_fill()   const = 0;
    };

    class StageBase {
        StageBase* next;
    public:
        virtual ~StageBase() = default;
        virtual void connect(StageBase* next) = 0;
        virtual void tick() = 0;
        virtual const char* get_name() const = 0;
    };

    template <class In, class Out>
    class Stage : public Process<In, Out>, public StageBase {
        void connect(StageBase* next) override {
            Sink<Out>* sink = dynamic_cast<Sink<Out>*>(next);
            if(!sink) {
				throw std::invalid_argument("The type of next is is invalid!!!");
                return;
            }
            this->set_consumer(sink);
        }
    };

    template <class In, class Out>
    class AtomicStage: public Stage<In, Out>, public AtomicStageBase {
    protected:
        std::queue<In> queue;
    public:
        explicit AtomicStage(u64 capacity):
            AtomicStageBase(capacity) {}

        u64 get_fill() const override {
            return queue.size();
        }

        b8 consume(const In& product) override {
            if(!can_consume()) return false;
            queue.push(product);
            return true;
        }

        b8 can_consume() override {
            return queue.size() < capacity;
        }

		
    };
}
