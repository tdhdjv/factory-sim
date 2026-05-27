#include "backend/test.h"
#include "core/window.h"

#include "ui/ui.h"


int main(int, char**) {

	LongDay::Window window(1200, 800, "Long Day Factory Simulation");

	LongDay::LongDayFactory longDayFactory;
	LongDay::PrintI32Sink printSink;
	longDayFactory.set_consumer(&printSink);
	for(u32 i = 0 ; i < 10; i++) {
		longDayFactory.feed();
		longDayFactory.tick();
		longDayFactory.consume(10);
		longDayFactory.print_status();
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

