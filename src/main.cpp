#include "core/logger.h"
#include "core/window.h"
#include "backend/scene.h"
#include "long_day_factory/long_day_factory.h"
#include "long_day_factory/hope_and_dream_source.h"
#include "long_day_factory/day_sink.h"
#include "new_ui/ui_manager.h"
#include <memory>

int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");
	
	auto normalSource  = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto normalFactory = std::make_unique<LongDay::LongDayFactory>(0);
	auto normalSink    = std::make_unique<LongDay::DaySink>();

	auto breakDownSource  = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto breakDownFactory = std::make_unique<LongDay::LongDayFactory>(0.01f);
	auto breakDownSink    = std::make_unique<LongDay::DaySink>();

	std::vector<LongDay::Scene<LongDay::HopeAndDreams, LongDay::Day>> scenes;

	scenes.emplace_back(
		std::move(normalSource),
		std::move(normalFactory),
		std::move(normalSink)
	);
	scenes.emplace_back(
		std::move(breakDownSource),
		std::move(breakDownFactory),
		std::move(breakDownSink)
	);

	LongDay::UIManager<LongDay::HopeAndDreams, LongDay::Day> uiManager(std::move(scenes));

	LongDay::Logger::log(LongDay::LogStatus::ERROR, "err");
	LongDay::Logger::log(LongDay::LogStatus::WARN, "warn");
	LongDay::Logger::log(LongDay::LogStatus::INFO, "info");

	while(window.is_running()) {
		window.update();
		uiManager.draw();
		window.render();
	}
}
