#include "ui/inspector.h"
#include "ui/ui_colors.h"
#include "ui/ui_state.h"

#include <imgui.h>

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


   void Inspector::draw(){
      ImGui::BeginChild("Inspector", {400, 300}, true);
      if(u_selectedMachine < 0 || u_selectedMachine >= (int)u_machines.size()){
         ImGui::Text("Inspector Window :)\n No machine selected.");
         ImGui::EndChild();
         return;
      }

      const auto& machine = u_machines[u_selectedMachine];  // temporary data not real, backend data will be used during integration 
      
      ImVec4 stateColors;
      switch(machine.state){
         case UI::MachineState::BROKEN:
            stateColors = UI::Colors::BROKEN;
            break;
         case UI::MachineState::WORKING:
            stateColors = UI::Colors::WORKING;
            break;
         case UI::MachineState::IDLE:
            stateColors = UI::Colors::IDLE;
            break;
      };

      ImGui::Text("Machine: %s", machine.label.c_str());
      ImGui::Separator();

      ImGui::Text("State:");
      ImGui::SameLine();
      ImGui::TextColored(stateColors, "%s", state_to_string(machine.state));

      ImGui::Text("Health: %.0f%%", machine.health);
      ImGui::Text("Progress:");
      ImGui::SameLine();
      ImGui::ProgressBar(machine.progress, ImVec2(-1, 20));
      ImGui::Text("Queue: %llu/%llu", machine.queueSize, machine.queueCapacity);
      ImGui::Text("Output: %llu", machine.outputCount);
      ImGui::Text("Process Time: %u ticks", machine.processTimeTicks);
      ImGui::Spacing();
      ImGui::Button("Force Break");
      ImGui::SameLine();
      ImGui::Button("Instant Repair");

      ImGui::EndChild();
   }
