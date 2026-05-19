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
	std::vector<LongDay::StageBase*> baseStages;
   std::vector<LongDay::AtomicStage<int,int>*> atomicStages;

   for (const auto& s : longDayFactory.get_stages()) {
      LongDay::StageBase* base = s.get();
      auto* atomic = dynamic_cast<LongDay::AtomicStage<int,int>*>(base);
      if (atomic) {
         baseStages.push_back(base);    // get_name
         atomicStages.push_back(atomic); // for get_fill(), get_size()
      }
   }

	while(window.is_running()) {
		window.update();
		//UI Here!
		LongDay::UI::render(baseStages, atomicStages);
		//
		window.render();
	}
}

