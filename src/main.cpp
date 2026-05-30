#include "backend/test.h"
#include "backend/scene.h"
#include "core/window.h"

#include "ui/ui.h"


int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");

	auto i32Source       = std::make_unique<LongDay::I32Source>();
	auto longDayFactory  = std::make_unique<LongDay::LongDayFactory>();
	auto printSink       = std::make_unique<LongDay::PrintI32Sink>();

	LongDay::Scene<i32, i32> scene(std::move(i32Source), std::move(longDayFactory), std::move(printSink));

	for(u32 i = 0 ; i < 10; i++) {
		scene.tick();
		scene.print_status();
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

