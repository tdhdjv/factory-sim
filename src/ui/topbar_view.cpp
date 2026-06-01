#include "ui/ui_classes.h"
#include <imgui.h>
#include<iostream>

namespace LongDay {
   void TopbarView::draw(){

      if(ImGui::Button("Start")){
         u_state.requestStart = true;
      };
      ImGui::SameLine();
      if(ImGui::Button("Pause")){
         u_state.paused = true;
      };

      ImGui::SameLine();
      if(ImGui::Button("Reset")){
         u_state.requestReset = true;
         u_state.tick = 0;
      };
      ImGui::SameLine();
      ImGui::SetNextItemWidth(150.f);
      u_state.simulationSpeed = 1;
      ImGui::SliderInt("Speed", &u_state.simulationSpeed, 1, 5, "%dx");
      ImGui::SameLine(1200.f, 0.f);
      
      const char* items[] = {"Normal flow", "BreakDown"};
      static int current_item = 0;

      ImGui::SetNextItemWidth(170.f);
      if(ImGui::Combo("Scenarios", &current_item, items, IM_ARRAYSIZE(items))){
         u_state.scenario = (current_item == 0) ? NORMAL_FLOW : BREAKDOWN;
      };
      ImGui::SameLine(1600.0f, 0.0f);

      std::string ticksCounter = "Ticks " + std::to_string(u_state.tick);

      if (ImGui::Button(ticksCounter.c_str())){
         u_state.requestTick = true;
         u_state.tick +=1;
      }
   };
}
