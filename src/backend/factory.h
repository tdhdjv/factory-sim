#pragma once
#include "backend/stage.h"
#include <any>

namespace LongDay{
	template<class In, class Out>
	class Factory: Stage<In, Out> {
	private:
		std::vector<StageAbstract*> stages;
	public:
		void set_consumer(Sink<Out>* consumer) override{
			Stage<std::any, Out>* back = dynamic_cast<Stage<std::any, Out>*>(stages.back());
			if(!back) {
				//TODO: Error the back stage doesn't output Out Type
				return;
			}
			back->set_consumer(back);
			this->consumer = back->consumer;
		}

		void append(StageAbstract* stage) {
			StageAbstract* back = stages.back();
			back->connect(stage);
			stages.push_back(stage);
		}

		void insert(u64 index, StageAbstract* stage) {
			if(index > 0) {
				StageAbstract* previous = stages[index-1];
				previous->connect(stage);
			}
			if(index < stages.size()) {
				StageAbstract* next = stages[index];
				stage->connect(next);
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
