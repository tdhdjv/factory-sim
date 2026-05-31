#pragma once
#include "ui/ui_data.h"
#include "ui/UI_view.h"
#include <imgui.h>
#include <vector>

class FactoryCanvas : public LongDay::UI_view {
   private:
   const std::vector<UI::MachineDisplayData>& u_machines;
   const std::vector<UI::ConveyorDisplayData>& u_conveyors;
   i32& u_selectedMachine;
   ImVec2 u_size;

   public:
   FactoryCanvas(const std::vector<UI::MachineDisplayData>& machines,
   const std::vector<UI::ConveyorDisplayData>& conveyors,
   i32& selectedMachine, ImVec2 size): u_machines(machines), u_conveyors(conveyors), u_selectedMachine(selectedMachine), u_size(size) {};
   
   void draw() override;
};