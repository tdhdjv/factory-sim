#include "creator.h"

namespace LongDay {
    template<typename Output>
    Creator<Output>::Creator(): Stage<Output, Output>(0) {};

    template<typename Output>
    void Creator<Output>::update() {
        Output output;
    }
}
