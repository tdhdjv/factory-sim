#include "ui/ui_manager.h"
#include <imgui.h>

namespace LongDay {

   UIManager::UIManager(Scene<HopeAndDreams, Day>& scene, UIState& state)
   :  u_state(state),
      u_topbar(state),
      u_sceneView(scene, state)
   {}

   void UIManager::draw() {
      ImGuiIO& io = ImGui::GetIO();
      ImGui::SetNextWindowPos({0, 0});
      ImGui::SetNextWindowSize(io.DisplaySize);
      ImGui::Begin("##host", nullptr,
         ImGuiWindowFlags_NoDecoration      |
         ImGuiWindowFlags_NoMove            |
         ImGuiWindowFlags_NoBringToFrontOnFocus
      );

      u_topbar.draw();
      ImGui::Spacing();
      u_sceneView.draw();

      ImGui::End();
   }

}
