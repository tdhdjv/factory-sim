#pragma once
#include "backend/utils.h"
#include "backend/stage.h"
#include "backend/machine_base.h"

namespace LongDay {
    template<typename In, typename Out>
    class Machine: public AtomicStage<In, Out>, public MachineBase {
    private:
        u32 progress;
        u32 ticksForProduction;
        b8 broken;
        u64 outputCount;
    protected:
        virtual Out transform(const In& input) = 0;
    public:
        explicit Machine(u32 capacity, u32 ticksForProduction, f32 failProbability)
            : AtomicStage<In, Out>(capacity),
              progress(0),
              ticksForProduction(ticksForProduction),
              broken(false),
              outputCount(0) {
            originalFailureProbability = failProbability;
            activeFailureProbability   = failProbability;
        };

        void tick() override {
            if(this->queue.empty()) return; 

            if(!broken && randomFloat() <= activeFailureProbability) {
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

        void fix() override {
            broken = false;
        }

        void reset() override {
            progress = 0;
            broken = false;
            outputCount = 0;

            while(!this->queue.empty()) this->queue.pop();
            activeFailureProbability = originalFailureProbability;

        }

        b8 is_broken() override {
            return broken;
        }

        u32 get_progress() const override { return progress; }
        u32 get_ticks_for_production() const override { return ticksForProduction; }
        u64 get_output_count() const override { return outputCount; }
    };
}
