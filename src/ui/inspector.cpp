#include "ui/inspector.h"
#include "ui/ui_colors.h"

#include <imgui.h>

namespace Inspector {

   static const char* state_to_string(UI::MachineState state){

      switch(state){
         case UI::MachineState::IDLE:
            return "IDLE";
         case UI::MachineState::WORKING:
            return "WORKING";
         case UI::MachineState::BROKEN:
            return "BROKEN";
         case UI::MachineState::MAINTENANCE:
            return "MAINTENANCE";
      }
      return "UNKNOWN";
   }

   void draw( const std::vector<UI::MachineDisplayData>& machines, int selectedMachine, ImVec2 size)
   {
      ImGui::BeginChild("Inspector", {400, 300}, true);
      if(selectedMachine < 0 || selectedMachine >= (int)machines.size()){
         ImGui::Text("Inspector Window :)\n No machine selected.");
         ImGui::EndChild();
         return;
      }

      const auto& machine = machines[selectedMachine];  // temporary data not real 

      ImGui::Text("Machine: %s", machine.label.c_str());
      ImGui::Separator();
      ImGui::Text("State: %s", state_to_string(machine.state));
      ImGui::Text("Health: %.0f%%", machine.health);
      ImGui::Text("Progress:");
      ImGui::SameLine();
      ImGui::ProgressBar(machine.progress, ImVec2(-1, 20));
      ImGui::Text("Queue: %llu/%llu", machine.queueSize, machine.queueCapacity);
      ImGui::Text("Output: %llu", machine.outputCount);
      ImGui::Text("Process Time: %u ticks", machine.processTimeTicks);

      ImGui::EndChild();
   }
}