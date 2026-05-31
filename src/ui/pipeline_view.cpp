#include "ui/ui_classes.h"
#include "ui/ui_colors.h"
#include <imgui.h>


namespace LongDay{

   static void draw_machine(const MachineDisplayData& machine, bool selected){
      if(selected){
         ImGui::PushStyleColor( ImGuiCol_Button, Colors::PRODUCT_DOT);
      }
      ImGui::Button(machine.label.c_str(), ImVec2(200, 100));
      if(selected){
         ImGui::PopStyleColor();
      }
      ImGui::Text("Queue: %llu/%llu", machine.queueSize, machine.queueCapacity);
      ImGui::ProgressBar( machine.progress, ImVec2(200, 20));
   }

   void PipelineView:: draw()
   {
      ImGui::BeginChild("Factory Pipeline", u_size, true);

      ImGui::BeginGroup();
      ImGui::Text("Dreams\nHopes");
      ImGui::EndGroup();
      ImGui::SameLine();
      ImGui::Text("->");
      ImGui::SameLine();

      for(size_t i = 0; i < u_machines.size(); ++i){
            ImGui::BeginGroup();
            draw_machine(u_machines[i], u_selectedMachine == (i32)i);
            ImGui::EndGroup();

            if(ImGui::IsItemClicked()){
               u_selectedMachine = (i32)i;
            }

            if(i < u_machines.size() - 1){
               ImGui::SameLine();
               ImGui::Text("->");
               ImGui::SameLine();
            }
      }

      ImGui::SameLine();
      ImGui::Text("->");
      ImGui::SameLine();
      ImGui::BeginGroup();
      ImGui::Text("Long\nHappy Days");
      ImGui::EndGroup();
      ImGui::SameLine();

      ImGui::EndChild();
   };
};
