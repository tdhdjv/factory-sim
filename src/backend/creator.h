#include "backend/stage.h"

namespace LongDay {
    template<typename Output>
    class Creator: public Stage<Output, Output> {
        Creator();
        void update() override;
    };
}
