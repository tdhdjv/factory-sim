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

	//vector for the UI
	std::vector<LongDay::AtomicStage<int, int>*> pipeline;
	for (const auto& s: longDayFactory.get_stages()) {
		auto* ptr = dynamic_cast<LongDay::AtomicStage<int, int>*>(s.get());
		if (ptr) pipeline.push_back(ptr);
	}


	while(window.is_running()) {
		window.update();
		//UI Here!
		LongDay::UI::render(pipeline);
		//
		window.render();
	}
}

