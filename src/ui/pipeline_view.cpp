#include "ui/ui_classes.h"
#include "ui/ui_colors.h"
#include <imgui.h>


namespace LongDay{

   static void draw_machine(const MachineDisplayData& machine, bool selected){
      if(selected){
         ImGui::PushStyleColor( ImGuiCol_Button, Colors::PRODUCT_DOT);
      }
      ImGui::Button(machine.label.c_str(), ImVec2(255, 100));
      if(selected){
         ImGui::PopStyleColor();
      }
      ImGui::Text("Queue: %llu/%llu", machine.queueSize, machine.queueCapacity);
      ImGui::ProgressBar( machine.progress, ImVec2(200, 30));
   }

   void PipelineView::draw()
   {
      ImGui::BeginChild("Factory Pipeline", u_size, true);

      ImGui::BeginGroup();
      ImGui::Text("Dreams\nHopes");
      ImGui::EndGroup();
      ImGui::SameLine();
      ImGui::Text("->");
      ImGui::SameLine();

      for(i32 i = 0; i < u_machines.size(); ++i){
            ImGui::BeginGroup();
            draw_machine(u_machines[i], u_selectedMachine == i);
            ImGui::EndGroup();

            if(ImGui::IsItemClicked()){
               u_selectedMachine = i;
            }

            if (i < u_conveyors.size()) {
               ImGui::SameLine();
               ImGui::BeginGroup();
               ImGui::Text("  conveyor\n==[%llu/%llu]==>", u_conveyors[i].itemCount, u_conveyors[i].capacity);
               ImGui::ProgressBar(u_conveyors[i].fillPercent, ImVec2(100,20));
               ImGui::EndGroup();
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
