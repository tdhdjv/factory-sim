#include "ui/factory_view.h"
#include "ui/stage_card.h"
#include "imgui.h"

namespace LongDay {
   namespace PipelineView {
      void draw(
         const std::vector<StageBase*>& baseStages,
         const std::vector<AtomicStage<int,int>*>& atomicStages
      ) {
         for (int i = 0; i < (int)baseStages.size(); i++) {
            StageCard::draw(baseStages[i], atomicStages[i], i);
            if (i < (int)baseStages.size() - 1) {
               ImGui::SameLine();
               ImGui::Text(" -> ");
               ImGui::SameLine();
            }
         }
      }
   }
}


