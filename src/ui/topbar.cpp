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
      ImGui::SliderFloat("Speed", &state.simulationSpeed, 0.1f, 5.0f, "%.1fx");
      ImGui::SameLine(1700.0f, 0.0f);
      ImGui::Button("Ticks");
   }

} 