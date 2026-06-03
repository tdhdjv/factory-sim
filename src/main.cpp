#include "core/window.h"
#include "ui/ui_manager.h"
#include "backend/scene.h"
#include "long_day_factory/long_day_factory.h"
#include "long_day_factory/hope_and_dream_source.h"
#include "long_day_factory/print_day_sink.h"
#include <memory>

int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");
	
	auto source  = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto factory = std::make_unique<LongDay::LongDayFactory>();
	auto sink    = std::make_unique<LongDay::PrintDaySink>();

	LongDay::Scene<LongDay::HopeAndDreams, LongDay::Day> scene(
		std::move(source),
		std::move(factory),
		std::move(sink)
	);

	LongDay::UIState state;
	LongDay::UIManager ui(scene, state);

	while(window.is_running()) {
		window.update();
		ui.draw();
		window.render();
	}
}
