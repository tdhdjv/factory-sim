#pragma once

namespace LongDay {
    //Interface
    class Stage {
        virtual void tick() = 0;
        virtual void print_status() = 0;
    };
}

