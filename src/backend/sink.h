#pragma once
#include "define.h"
#include "backend/stage.h"

namespace LongDay {
    //Interface
    template <class T>
    class Sink: Stage {
    public:
        //The return value tells us if it successfully consumed
        virtual b8 can_consume() = 0;
        virtual b8 consume(const T& product) = 0;
    };
}
