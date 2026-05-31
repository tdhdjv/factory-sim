#pragma once
#include "ui/ui_data.h"
#include "ui/ui_state.h"
#include <vector>

class FactoryUI {

   public:
   void draw(
      LongDayFactoryState& state,
      const std::vector<UI::MachineDisplayData>& machines,
      const std::vector<UI::ConveyorDisplayData>& conveyors,
      const UI::FactoryStats& stats,
      const std::vector<UI::LogEntry>& logs
   );

};



