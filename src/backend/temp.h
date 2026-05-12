#pragma once
#include "backend/stage.h"
#include "creator.h"

namespace LongDay {
    class Temp: public Stage<i32, i32> {
    public:
        Temp(); 
        void update() override;
    };

    class I32Creator: public Creator<i32> {
    public:
        i32 create_output() override;
    };
}
