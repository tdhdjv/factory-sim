#include "core/window.h"
#include "ui/ui_manager.h"
#include "backend/scene.h"
#include "long_day_factory/long_day_factory.h"
#include "long_day_factory/hope_and_dream_source.h"
#include "long_day_factory/day_sink.h"
#include <memory>

int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");
	
	auto normalSource  = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto normalFactory = std::make_unique<LongDay::LongDayFactory>(0);
	auto normalSink    = std::make_unique<LongDay::DaySink>();

	auto breakDownSource  = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto breakDownFactory = std::make_unique<LongDay::LongDayFactory>(0.1f);
	auto breakDownSink    = std::make_unique<LongDay::DaySink>();

	LongDay::Scene<LongDay::HopeAndDreams, LongDay::Day> normalScene(
		std::move(normalSource),
		std::move(normalFactory),
		std::move(normalSink)
	);

	LongDay::Scene<LongDay::HopeAndDreams, LongDay::Day> breakDownScene(
		std::move(breakDownSource),
		std::move(breakDownFactory),
		std::move(breakDownSink)
	);

	LongDay::UIState state;
	LongDay::UIManager ui(normalScene, state);

	while(window.is_running()) {
		window.update();
		ui.draw();
		window.render();
	}
}
