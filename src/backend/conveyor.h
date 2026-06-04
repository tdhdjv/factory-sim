#pragma once
#include "backend/stage.h"

namespace LongDay {
    template<typename T>
    class Conveyor: public AtomicStage<T,T> {
    private:
    public:
        explicit Conveyor(i32 capacity): AtomicStage<T,T> (capacity) {};
        void tick() override {
            if(this->queue.empty()) return; 
            if(!this->consumer->can_consume()) return;
            feed();
        }

        void reset(){
            while (!this->queue.empty()){
                this->queue.pop();
            }
        }

        b8 feed() override {
			if(this->queue.empty())
				return false;
            this->consumer->consume(this->queue.front());
            this->queue.pop();
            return true;
        }

		const char* get_name() const override{
			return "conveyor";
		}
    };
}

