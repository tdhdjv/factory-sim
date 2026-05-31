#include "core/window.h"

#include "ui/ui.h"
#include "backend/scene.h"
#include "long_day_factory/long_day_factory.h"
#include <memory>

int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");
	
	auto source = std::make_unique<LongDay::HopeAndDreamsSource>();
	auto factory = std::make_unique<LongDay::LongDayFactory>();
	auto sink = std::make_unique<LongDay::PrintDaySink>();

	LongDay::Scene<LongDay::HopeAndDreams, LongDay::Day> scene(
		std::move(source),
		std::move(factory),
		std::move(sink)
	);

	for(u32 i = 0; i < 100; i++) {
		scene.tick();
	}

	//vectors for the UI
	LongDayFactoryState state;
	std::vector<UI::MachineDisplayData>  machines;
    std::vector<UI::ConveyorDisplayData> conveyors;
    UI::FactoryStats                     stats;
    std::vector<UI::LogEntry>            logs;

	while(window.is_running()) {
		window.update();
		//UI Here!
		FactoryUI::draw(state, machines, conveyors, stats, logs);
		//
		window.render();
	}
}

