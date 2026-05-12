#include "backend/process.h"

namespace LongDay {
    template<typename In, typename Out>
    class Machine: public Process<In, Out> {
    protected:
        virtual Out transform(const In& input) = 0;
    public:
        Machine(u32 capacity): Process<In, Out>(capacity) {};

        void tick() override {
            if(this->queue.empty()) return; 
            if(!this->consumer->can_consume()) return;
            feed();
        }

        b8 feed() override {
            this->consumer->consume(transform(this->queue.front()));
            this->queue.pop();
            return true;
        }
    };
}

