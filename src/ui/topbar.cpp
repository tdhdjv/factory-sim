#include "ui/topbar.h"
#include <imgui.h>

namespace Topbar {

void draw(LongDayFactoryState& state) {
   ImGui::Button("Start");
   ImGui::SameLine();
   ImGui::Button("Pause");
   ImGui::SameLine();
   ImGui::Button("Reset");
   ImGui::SameLine();
   ImGui::SetNextItemWidth(150.f);
   ImGui::SliderFloat("Speed", &state.simulationSpeed, 0.1f, 5.0f, "%.1fx");
}

} 