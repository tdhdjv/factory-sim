#include "ui/stage_card.h"
#include "imgui.h"

namespace LongDay {
   namespace StageCard {
      void draw(AtomicStage<int, int>* stage, int id) {
         ImGui::PushID(id);
         ImGui::BeginGroup();

         ImGui::Text("%s", stage->get_name());

         float fill = stage->get_fill();
         ImVec4 color = (fill >= 1.0f)
            ? ImVec4(0.9f, 0.2f, 0.2f, 1.f)
            : ImVec4(0.3f, 0.75f, 0.4f, 1.f);

         ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);
         char label[32];
         snprintf(label, sizeof(label), "%llu/%llu", stage->get_size(), stage->get_capacity());
         ImGui::ProgressBar(fill, ImVec2(110, 0), label);
         ImGui::PopStyleColor();

         ImGui::EndGroup();
         ImGui::PopID();
      }
   }
}

