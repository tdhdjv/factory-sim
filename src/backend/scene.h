#include "backend/factory.h"
#include "backend/sink.h"
#include "backend/source.h"

namespace LongDay {
	template<class In, class Out>
	class Scene {
	private:
		std::unique_ptr<Source<In>> source;
		std::unique_ptr<Factory<In, Out>> factory;
		std::unique_ptr<Sink<Out>> sink;
	public:
		Scene(std::unique_ptr<Source<In>> source, std::unique_ptr<Factory<In, Out>> factory, std::unique_ptr<Sink<Out>> sink) {
			this->source = std::move(source);
			this->factory = std::move(factory);
			this->sink = std::move(sink);
			this->source->set_consumer(this->factory.get());
			this->factory->set_consumer(this->sink.get());
		};

		void tick() {
			factory->feed();
			factory->tick();
			source->feed();
		}

		virtual void print_status() {
			factory->print_status();
		}
	};
}
