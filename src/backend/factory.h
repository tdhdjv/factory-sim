#pragma once
#include "backend/stage.h"
// #include <any>

namespace LongDay{
	template<class In, class Out>
	class Factory: Process<In, Out> {
	private:
		b8 consumerSycned = false;
		std::vector<StageBase*> stages;
	public:
		void set_consumer(Sink<Out>* consumer) override{
			if(!consumerSycned) {
				Stage<std::any, Out>* back = dynamic_cast<Stage<std::any, Out>*>(stages.back());
				if(!back) {
					//TODO: Error the back stage doesn't output Out Type
					return;
				}
				this->consumer = back->consumer;
				consumerSycned = true;
			}
			this->set_consumer(consumer);
		}

		void append(StageBase* stage) {
			StageBase* back = stages.back();
			if(back)
				back->connect(stage);
			stages.push_back(stage);
			consumerSycned = false;
		}

		void insert(u64 index, StageBase* stage) {
			if(index > 0) {
				StageBase* previous = stages[index-1];
				previous->connect(stage);
			}
			if(index < stages.size()) {
				StageBase* next = stages[index];
				stage->connect(next);
			}
			else {
				//When the insert index is in the back
				consumerSycned = false;
			}
			stages.insert(stages.begin() + index, stage);
		}

		void tick() override {
			//tick in reverse order
			for(auto stage = stages.back()-1; stage >= stages.front(); stage--) {
				stage->tick();
			}
		}
	};
}

