#include "ui/topbar.h"

#include "ui/ui_state.h"

#include <imgui.h>

namespace Topbar {

void draw(){

   ImGui::Begin("Topbar");
   ImGui::Button("Start");
   ImGui::SameLine();
   ImGui::Button("Pause");
   ImGui::SameLine();
   ImGui::Button("Reset");
   ImGui::SameLine();

   ImGui::SetNextItemWidth(180);

   LongDayFactoryState speed;

   ImGui::SliderFloat(
      "Simulation Speed",
      &speed.simulationSpeed,
      0.1f,
      5.0f
   );

   ImGui::End();
}

}