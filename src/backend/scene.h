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

		// When true, machines use their built-in failure probability.
		// When false (NORMAL_FLOW), we override to 0 so no breakdowns happen.
		bool breakdownMode = false;

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

		// Accessors for SceneView
		Source<In>* get_source() { return source.get(); }
		Factory<In, Out>* get_factory() { return factory.get(); }
		Sink<Out>* get_sink() { return sink.get(); }

		bool is_breakdown_mode() const { return breakdownMode; }

		// Set breakdown mode: enable/disable random machine failures.
		// When disabled we forcibly fix all broken machines so they don't stay
		// stuck broken after a mode switch.
		void set_breakdown_mode(bool enabled) {
			breakdownMode = enabled;
			if (!enabled) {
				// Fix all broken machines when switching back to normal flow
				for (auto& stagePtr : factory->get_stages()) {
					StageBase* base = stagePtr.get();
					// Try to cast to a Machine-like object via MachineBase
					// We use MachineBase (see below) to avoid template issues
					if (auto* m = dynamic_cast<MachineBase*>(base)) {
						if (!enabled) m->fix();
						m->set_active_failure_probability(enabled ? m->get_failure_probability() : 0.0f);
					}
				}
			} else {
				// Restore original failure probabilities
				for (auto& stagePtr : factory->get_stages()) {
					if (auto* m = dynamic_cast<MachineBase*>(stagePtr.get())) {
						m->set_active_failure_probability(m->get_failure_probability());
					}
				}
			}
		}
	};
}
