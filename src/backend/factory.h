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
		}

		void append(StageAbstract* stage) {
			StageAbstract* back = stages.back();
			back->connect(stage);
			stages.push_back(stage);
		}

		void insert(u64 index, StageAbstract* stage) {
			if(index != 0) {
				StageAbstract* previous = stages[index-1];
			}

		}
		void tick() override {

		}
	};
}
