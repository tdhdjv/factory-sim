#pragma once
#include "backend/stage.h"

namespace LongDay {
    template<typename In, typename Out>
    class Machine: public AtomicStage<In, Out> {
    private:
        u32 progress;
        u32 ticksForProduction;
    protected:
        virtual Out transform(const In& input) = 0;
    public:
        explicit Machine(u32 capacity, u32 ticksForProduction): AtomicStage<In, Out>(capacity), progress(0), ticksForProduction(ticksForProduction) {};

        void tick() override {
            if(this->queue.empty()) return; 
            progress++;
            if(progress >= ticksForProduction) {
                feed();
                progress = 0;
            }
        }

        b8 feed() override {
			if(this->queue.empty())
				return false;
            this->consumer->consume(transform(this->queue.front()));
			this->queue.pop();
            return true;
        }
    };
}
