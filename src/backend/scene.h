#pragma once
#include "backend/factory.h"
#include "backend/sink.h"
#include "backend/source.h"
#include "backend/machine.h"

namespace LongDay {
	template<class In, class Out>
	class Scene {
	private:
		std::unique_ptr<Source<In>> source;
		std::unique_ptr<Factory<In, Out>> factory;
		std::unique_ptr<Sink<Out>> sink;

	public:
		Scene(std::unique_ptr<Source<In>> source, std::unique_ptr<Factory<In, Out>> factory, std::unique_ptr<Sink<Out>> sink)
		:source(std::move(source)), factory(std::move(factory)), sink(std::move(sink)) {
			this->source->set_consumer(this->factory.get());
			this->factory->set_consumer(this->sink.get());
		}

		void tick() {
			factory->feed();
			factory->tick();
			source->feed();
		}

		Source<In>* get_source() { return source.get(); }
		Factory<In, Out>* get_factory() { return factory.get(); }
		Sink<Out>* get_sink() { return sink.get(); }
	};
}
