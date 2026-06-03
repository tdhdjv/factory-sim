#pragma once

#include <iostream>
#include "backend/process.h"
#include <queue>

namespace LongDay {

    // Non-template interface so SceneView can read queue info from any
    // AtomicStage without knowing its template parameters.
    class AtomicStageAccessor {
    public:
        virtual ~AtomicStageAccessor() = default;
        virtual u64 get_size()     const = 0;
        virtual u64 get_capacity() const = 0;
        virtual float get_fill()   const = 0;
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
                //TODO: Error for wrong type of connect
                return;
            }
            this->set_consumer(sink);
        }
    };

    // An AtomicStage is a Stage that isn't composed out of other stages.
    // It also inherits AtomicStageAccessor so SceneView can query queue info.
    template <class In, class Out>
    class AtomicStage: public Stage<In, Out>, public AtomicStageAccessor {
    protected:
        std::queue<In> queue;
        u64 capacity;
    public:
        explicit AtomicStage(u64 capacity):
            capacity(capacity) {}

        u64 get_size()     const override { return queue.size(); }
        u64 get_capacity() const override { return capacity; }
        float get_fill()   const override {
            return (float)queue.size() / (float)capacity;
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
