#pragma once
#include "ui/ui_data.h"
#include "ui/UI_view.h"
#include <imgui.h>

class Inspector : public LongDay::UI_view {
   private:
   const std::vector<UI::MachineDisplayData>& u_machines;
   int& u_selectedMachine;
   ImVec2 u_size;
   public:
   Inspector(const std::vector<UI::MachineDisplayData>& machines, int& selectedMachine, ImVec2 size):
   u_machines(machines), u_selectedMachine(selectedMachine), u_size(size){};
   void draw() override;
};
