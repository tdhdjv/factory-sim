#pragma once
#include "ui/ui_data.h"
#include <imgui.h>
#include <vector>

namespace FactoryCanvas {
   void draw(
      const std::vector<UI::MachineDisplayData>&  machines,
      const std::vector<UI::ConveyorDisplayData>& conveyors,
      int& selectedMachine, ImVec2 size
   );
}