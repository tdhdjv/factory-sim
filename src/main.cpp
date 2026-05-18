#include "backend/test.h"
#include "core/window.h"

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
	while(window.is_running()) {
		window.update();
		//UI Here!
		window.render();
	}
}

