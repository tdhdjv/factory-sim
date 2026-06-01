#include "ui/ui_classes.h"
#include "ui/ui_colors.h"
#include "ui/ui_data.h"
#include <imgui.h>

namespace LongDay{

    static const char* state_to_string(MachineState state){
          switch(state){
             case MachineState::IDLE:
                return "IDLE";
             case MachineState::WORKING:
                return "WORKING";
             case MachineState::BROKEN:
                return "BROKEN";
             case MachineState::MAINTENANCE:
                return "MAINTENANCE";
          }
          return "UNKNOWN";
       }


      void InspectorView::draw(){
         ImGui::BeginChild("Inspector", {400, 300}, true);
         
         if(u_selectedMachine < 0 || u_selectedMachine >= (i32)u_machines.size()){
            ImGui::Text("Inspector Window :)\n No machine selected.");
            ImGui::EndChild();
            return;
         }

         const auto& machine = u_machines[u_selectedMachine];  
         
         ImVec4 stateColors;
         switch(machine.state){
            case MachineState::BROKEN:
               stateColors = Colors::BROKEN;
               break;
            case MachineState::WORKING:
               stateColors = Colors::WORKING;
               break;
            case MachineState::IDLE:
               stateColors = Colors::IDLE;
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
      };
};
