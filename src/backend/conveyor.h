#include "backend/process.h"

namespace LongDay {
    template<typename T>
    class Conveyor: public Process<T,T> {
    private:
    public:
        void tick() override {
            if(this->queue.empty()) return; 
            if(!this->consumer->can_consume()) return;
            feed();
        }

        b8 feed() override {
            this->consumer.consume(this->queue.front());
            this->queue.pop();
        }
    };
}

