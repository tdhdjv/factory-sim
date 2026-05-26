#include "ui/topbar.h"
#include <imgui.h>

namespace Topbar {

   void draw(LongDayFactoryState& state) {
      if(ImGui::Button("Start")){
         state.requestStart = true;
      };
      ImGui::SameLine();
      if(ImGui::Button("Pause")){
         state.paused = true;
      };
      ImGui::SameLine();
      if(ImGui::Button("Reset")){
         state.requestReset = true;
      };
      ImGui::SameLine();
      ImGui::SetNextItemWidth(150.f);
      state.simulationSpeed = 1;
      ImGui::SliderInt("Speed", &state.simulationSpeed, 1, 5, "%dx");
      ImGui::SameLine(1700.0f, 0.0f);
      if (ImGui::Button("Ticks")){
         state.requestTick = true;
         state.tick +=1;
      };
   }

} 