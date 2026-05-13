#pragma once
#include "backend/stage.h"

namespace LongDay {
    template<typename T>
    class Conveyor: public Stage<T,T> {
    private:
    public:
        Conveyor(i32 capacity): Process<T,T> (capacity) {};
        void tick() override {
            if(this->queue.empty()) return; 
            if(!this->consumer->can_consume()) return;
            feed();
        }

        b8 feed() override {
            this->consumer->consume(this->queue.front());
            this->queue.pop();
            return true;
        }
    };
}

