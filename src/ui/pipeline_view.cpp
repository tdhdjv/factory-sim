#include "ui/pipeline_view.h"
#include "ui/stage_card.h"
#include "imgui.h" 

namespace LongDay {
   namespace PipelineView {
      void draw(const std::vector<AtomicStage<int, int>*>& stages) {
         for (int i = 0; i < (int)stages.size(); i++) {
            StageCard::draw(stages[i], i);
            if (i < (int)stages.size() - 1) {
               ImGui::SameLine();
               ImGui::Text(" -> ");
               ImGui::SameLine();
            }
         }
      }
   }
}
