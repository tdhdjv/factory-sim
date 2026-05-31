#include "core/window.h"

#include "ui/ui_manager.h"
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
	LongDay::FactoryState state;
	std::vector<LongDay::MachineDisplayData>  machines;
   std::vector<LongDay::ConveyorDisplayData> conveyors;
   LongDay::FactoryStats                     stats;
   std::vector<LongDay::LogEntry>            logs;

	LongDay::UIManager ui(state, machines, conveyors, stats, logs); 


	while(window.is_running()) {
		window.update();
		//UI Here!
		ui.draw();
		//
		window.render();
	}
}

