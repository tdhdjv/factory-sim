#pragma once
#include "backend/utils.h"
#include "backend/stage.h"
#include "backend/machine_base.h"
#include "core/logger.h"
#include <iostream>

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
				Logger::log(LogStatus::WARN, "%s Broke!!!", this->get_name());
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
			Logger::log(LogStatus::INFO, "%s has been Fixed!", this->get_name());
		}

		void break_machine() override {
			broken = true;
			Logger::log(LogStatus::WARN, "%s has been forcablity broken!!!", this->get_name());
		}

		std::string get_str() const override  {
			return this->get_name();
		}

		u64 get_queue_cap() const override {
			return this->capacity;
		}

		u64 get_queue_fill() const override {
			return this->queue.size();
		}
    };
}
