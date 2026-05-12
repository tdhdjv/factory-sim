#include "define.h"
#include <any>
#include <queue>

namespace LongDay {
    template<typename Input, typename Output>
    class Stage {
    private:
        Stage<Output, std::any>* next;
        std::queue<Input> queue;
        u32 capacity;
    public:
        Stage(u32 capacity);

        void setNext(Stage<Output, std::any>* next);
        Stage<Output, std::any>* getNext();
            
        u32 get_capacity() const;
        u32 get_queue_length() const;

        b8 is_full() const;
        //The return value tells us if the push was successful or not
        //It returns true if the push successed, false if it failed
        b8 push_into(Input& input);

        virtual void update() = 0;
    };
}
