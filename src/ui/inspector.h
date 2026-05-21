#pragma once

#include "ui/ui_data.h"
#include <imgui.h>

namespace Inspector {
   void draw(
      const std::vector<UI::MachineDisplayData>& machines,
      int selectedMachine,
      ImVec2 size
   );
}