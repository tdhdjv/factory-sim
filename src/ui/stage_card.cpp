#include "ui/stage_card.h"
#include "imgui.h"

namespace LongDay {
   namespace StageCard {
      void draw(StageBase* AtomicStage, int id){
         ImGui::PushID(id);
         ImGui::BeginGroup();

         ImGui::Text("%s", AtomicStage->get_name());

         float fill = AtomicStage ->get_fill();
         ImVec4 color = (fill >= 1.0f)
            ? ImVec4(0.9f, 0.2f, 0.2f, 1.f) // when it is full -> becomes red
            : ImVec4(0.3f, 0.75f, 0.4f, 1.f); //when it is normal -> it is green


         
         ImGui::PushStyleColor(ImGuiCol_PlotHistogram, color);
         char label[32];
         snprintf(label, sizeof(label), "%u/%u", AtomicStage->get_size(), AtomicStage->get_capacity());
         ImGui::ProgressBar(fill, ImVec2(110, 0), label);
         ImGui::PopStyleColor();

         ImGui::EndGroup();
         ImGui::PopID();
      }
   }

}