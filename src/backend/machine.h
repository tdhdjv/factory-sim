#pragma once
#include "backend/utils.h"
#include "backend/stage.h"

namespace LongDay {
    template<typename In, typename Out>
    class Machine: public AtomicStage<In, Out> {
    private:
        u32 progress;
        u32 ticksForProduction;
		f32 failureProbability;
		b8 broken;
    protected:
        virtual Out transform(const In& input) = 0;
    public:
		explicit Machine(u32 capacity, u32 ticksForProduction, f32 failProbability)
			: AtomicStage<In, Out>(capacity),
			  progress(0),
			  ticksForProduction(ticksForProduction),
			  broken(false),
			  failureProbability(failProbability) {};
        void tick() override {
            if(this->queue.empty()) return; 

			if(randomFloat() <= failureProbability) {
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
            return true;
        }

		void fix() {
			broken = false;
		}

		f32 get_failure_probability() {
			return failureProbability;
		}

		b8 is_broken() {
			return broken;
		}
	};
}
