#pragma once
#include "define.h"
#include <any>
#include <queue>
#include <iostream>

namespace LongDay {
    template<typename Input, typename Output>
    class Stage {
    private:
        Stage<Output, std::any>* next;
        std::queue<Input> queue;
        u32 capacity;
    public:
        Stage(u32 capacity);

        void set_next(Stage<Output, std::any>* next);
        Stage<Output, std::any>* get_next();
            
        u32 get_capacity() const;
        u32 get_queue_length() const;

        b8 is_full() const;
        //The return value tells us if the push was successful or not
        //It returns true if the push successed, false if it failed
        b8 push_into(Input& input);

        virtual void update() = 0;

        //TODO: Temp, Only for debuggin purposes
        virtual void print_status();
    };

    template<typename Input, typename Output>
    Stage<Input, Output>::Stage(u32 capacity)
    :capacity(capacity), next(nullptr) {};

    template<typename Input, typename Output>
    void Stage<Input, Output>::set_next(Stage<Output, std::any>* next) {
        this->next = next;
    }

    template<typename Input, typename Output>
    Stage<Output, std::any>* Stage<Input, Output>::get_next() {
        return next;
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

    template<typename Input, typename Output>
    void Stage<Input, Output>::print_status() {
         std::queue<Input> copy = queue;
        std::cout << "Queue (" << copy.size() << "): [ ";
        while (!copy.empty()) {
            std::cout << copy.front() << " ";
            copy.pop();
        }
        std::cout << "]" << std::endl;
    }
}
