#include "ui/factory_canvas.h"
#include "ui/ui_colors.h"

#include <imgui.h>

namespace FactoryCanvas {

static void draw_machine(
   const UI::MachineDisplayData& machine,
   bool selected
){
   if(selected){
      ImGui::PushStyleColor(
         ImGuiCol_Button,
         UI::Colors::PRODUCT_DOT
      );
   }

   ImGui::Button(
      machine.label.c_str(),
      ImVec2(150, 90)
   );

   if(selected){
      ImGui::PopStyleColor();
   }

   ImGui::Text("Queue: %llu/%llu",
      machine.queueSize,
      machine.queueCapacity
   );

   ImGui::ProgressBar(
      machine.progress,
      ImVec2(150, 10)
   );
}

void draw(
   const std::vector<UI::MachineDisplayData>& machines,
   int& selectedMachine
){
   ImGui::Begin("Factory Pipeline");

   for(size_t i = 0; i < machines.size(); ++i){

      ImGui::BeginGroup();

      draw_machine(
         machines[i],
         selectedMachine == (int)i
      );

      if(ImGui::IsItemClicked()){
         selectedMachine = (int)i;
      }

      ImGui::EndGroup();

      if(i < machines.size() - 1){
         ImGui::SameLine();

         ImGui::Text("->");

         ImGui::SameLine();
      }
   }

   ImGui::End();
}

}