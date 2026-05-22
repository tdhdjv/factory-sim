#include "ui/factory_canvas.h"
#include "ui/ui_colors.h"

#include <imgui.h>

namespace FactoryCanvas {

   static void draw_machine(const UI::MachineDisplayData& machine, bool selected){
      
      if(selected){
         ImGui::PushStyleColor( ImGuiCol_Button, UI::Colors::PRODUCT_DOT);
      }

      ImGui::Button(machine.label.c_str(), ImVec2(180, 100));
      if(selected){
         ImGui::PopStyleColor();
      }

      ImGui::Text("Queue: %llu/%llu", machine.queueSize, machine.queueCapacity);
      ImGui::ProgressBar( machine.progress, ImVec2(180, 20));
   }

   void draw(
      const std::vector<UI::MachineDisplayData>& machines,
      const std::vector<UI::ConveyorDisplayData>& conveyors,
      int& selectedMachine,
      ImVec2 size ) 
   {
      ImGui::BeginChild("Factory Pipeline", size, true);

      ImGui::BeginGroup();
      ImGui::Text("Raw material");
      ImGui::EndGroup();
      ImGui::SameLine();
      ImGui::Text("->");
      ImGui::SameLine();

      for(size_t i = 0; i < machines.size(); ++i){
            ImGui::BeginGroup();
            draw_machine(machines[i], selectedMachine == (int)i);
            ImGui::EndGroup();

            if(ImGui::IsItemClicked()){
               selectedMachine = (int)i;
            }

            if(i < machines.size() - 1){
               ImGui::SameLine();
               ImGui::Text("->");
               ImGui::SameLine();
            }
      }

      ImGui::SameLine();
      ImGui::Text("->");
      ImGui::SameLine();
      ImGui::BeginGroup();
      ImGui::Text("Output");
      ImGui::EndGroup();
      ImGui::SameLine();

      ImGui::EndChild();
   }

}