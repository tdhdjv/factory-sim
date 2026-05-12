#include "stage.h"
#include <queue>

namespace LongDay {
    template<typename Input, typename Output>
    Stage<Input, Output>::Stage(u32 capacity)
    :capacity(capacity), next(nullptr) {};

    template<typename Input, typename Output>
    Stage<Output, std::any>* Stage<Input, Output>::getNext() {
        return next;
    }

    template<typename Input, typename Output>
    void Stage<Input, Output>::setNext(Stage<Output, std::any>* next) {
        this->next = next;
    }

    template<typename Input, typename Output>
    u32 Stage<Input, Output>::get_capacity() const {
        return capacity;
    }
    
    template<typename Input, typename Output>
    u32 Stage<Input, Output>::get_queue_length() const {
        return queue.size();
    }

    template<typename Input, typename Output>
    b8 Stage<Input, Output>::is_full() const {
        return queue.size() == capacity;
    }

    template<typename Input, typename Output>
    b8 Stage<Input, Output>::push_into(Input& input) {
        if(is_full()) return false;
        queue.push(input);
        return true;
    }
}
