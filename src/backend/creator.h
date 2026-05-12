#pragma once
#include "backend/stage.h"

namespace LongDay {
    template<typename Output>
    class Creator: public Stage<Output, Output> {
        public:
        Creator();
        virtual Output create_output() = 0;
        void update() override;
    };

    template<typename Output>
    Creator<Output>::Creator(): Stage<Output, Output>(0) {};

    template<typename Output>
    void Creator<Output>::update() {
        Output output = create_output();
        this->get_next()->push_into(output);
    }
}
