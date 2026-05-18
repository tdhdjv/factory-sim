#include "ui/ui.h"
#include "ui/pipeline_view.h"

namespace LongDay {
   namespace UI {
      void render(const std::vector<AtomicStage<int, int>*>& stages) {
         ImGui::SetNextWindowSize(ImVec2(900, 160), ImGuiCond_FirstUseEver);
         ImGui::Begin("Factory Pipeline");
         PipelineView::draw(stages);
         ImGui::End();

         //for controls window
         ImGui::SetNextWindowSize(ImVec2(200, 90), ImGuiCond_FirstUseEver);
         ImGui::SetNextWindowSize(ImVec2(85, 210), ImGuiCond_FirstUseEver);
         //new controls window
         ImGui::Begin("Controls");
         static int tickCount = 0; // shows how many ticks happened
         if (ImGui::Button("Tick")) {
            //tick in reverse order so items flow correctly
            for (int i = (int)stages.size()-1; i>=0; i--) {
               stages[i]->tick();
            }
            tickCount ++;
         }
         ImGui::Text("Tick: %d", tickCount);
         ImGui::End();
      }
   }
}