#pragma once
#include "backend/utils.h"
#include "backend/stage.h"
#include "backend/machine_base.h"

namespace LongDay {
    template<typename In, typename Out>
    class Machine: public AtomicStage<In, Out>, public MachineBase {
    private:
    protected:
        virtual Out transform(const In& input) = 0;
    public:
        explicit Machine(u64 capacity, u32 ticksForProduction, f32 failureProbability)
            : AtomicStage<In, Out>(capacity), MachineBase(ticksForProduction, failureProbability) {};

        void tick() override {
            if(this->queue.empty()) return; 

            if(!broken && randomFloat() <= failureProbability) {
                broken = true;
            }
            if(!broken) {
                progress++;
                if(progress >= ticksForProduction) {
                    feed();
                    progress = 0;
                }
            }
        }

        b8 feed() override {
            if(this->queue.empty())
                return false;
            this->consumer->consume(transform(this->queue.front()));
            this->queue.pop();
            outputCount++;
            return true;
        }
    };
}
