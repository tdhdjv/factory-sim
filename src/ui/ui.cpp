
#include "ui/ui.h"
#include "ui/pipeline_view.h"

namespace LongDay {
   namespace UI {
      void render(const std::vector<StageBase*>& stages) {  
         ImGui::SetNextWindowSize(ImVec2(900, 160), ImGuiCond_FirstUseEver);
         ImGui::Begin("Factory Pipeline");
         PipelineView::draw(stages);  
         ImGui::End();
      }
   }
}