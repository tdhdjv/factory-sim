#pragma once
#include "backend/stage.h"
#include <memory>

namespace LongDay{
	template<class In, class Out>
	class Factory: public Stage<In, Out> {
	private:
		b8 consumerSycned = false;
		std::vector<std::unique_ptr<StageBase>> stages;
	public:
		void sync_consumer() {
			if(!consumerSycned) {
				Source<Out>* back = dynamic_cast<Source<Out>*>(stages.back().get());
				if(!back) {
					//TODO: Error the back stage doesn't output Out Type
					return;
				}
				back->set_consumer(this->consumer);
				consumerSycned = true;
			}
		}
		void set_consumer(Sink<Out>* consumer) {
			this->consumer = consumer;
			sync_consumer();
		}
		Factory& append(std::unique_ptr<StageBase> stage) {
			if(!stages.empty()) {
				StageBase* back = stages.back().get();
				if(back)
					back->connect(stage.get());
			}
			stages.push_back(std::move(stage));
			consumerSycned = false;
			return *this;
		}

		void print() {
			for(auto& stage: stages) {
				stage->print_status();
			}
		}

		void tick() override {
			sync_consumer();
			for(u32 i = 0; i < stages.size(); i++) {
				stages[stages.size()-i-1].get()->tick();
			}
		}

		b8 can_consume() override {
			return true;
		}

		b8 consume(const In& product) override {
			if(stages.empty()) 
				return false;
			Sink<In>* frontStage = dynamic_cast<Sink<In>*>(stages.front().get());
			if(!frontStage)
				return false;
			return frontStage->consume(product);
		}

		b8 feed() override {
			if(stages.empty()) return false;
			sync_consumer();
			Source<Out>* backStage = dynamic_cast<Source<Out>*>(stages.back().get());
			if(!backStage) return false;
			return backStage->feed();
		}

		void print_status() override {
			std::cout << "(" << this->get_name() << ") [";
			for(auto& stage: stages) {
				if(stage) {
					stage->print_status();
					std::cout << " -> ";
				}
			}
			std::cout << "]";
			std::cout << std::endl;
		}
	};
}
