#include "ui/ui_classes.h"
#include <iostream>
#include "ui/ui_manager.h"
#include <imgui.h>

// Temporary data, the real data will be included during integration
namespace LongDay{
   std::vector<MachineDisplayData> makeMockMachines() {
      return {
         { "m1", "Double Machine 01", MachineState::WORKING,     92.f, 0.60f, 3, 5, 17, 3 },
         { "m2", "Double Machine 02", MachineState::IDLE,        100.f, 0.00f, 0, 5, 12, 5 },
         { "m3", "Double Machine 03", MachineState::BROKEN,      20.f, 0.00f, 1, 5, 8,  4 },
      };
   }

   std::vector<ConveyorDisplayData> makeMockConveyors() {
      return {
         { "c1", "C1", 2, 5, 0.4f },
         { "c2", "C2", 1, 5, 0.2f },
      };
   }

   FactoryStats makeMockStats() {
      return { 31, 4, 1, 0 };
   }

   std::vector<LogEntry> makeMockLogs() {
      return {
         { 125, "Double MAchine 01 BROKEN!",           LogStatus::DANGER },
         { 122, "Double MAchine 02 started processing", LogStatus::INFO   },
         { 120, "Double Machine 03 finished LongDay",   LogStatus::OK     },
         { 110, "Double Machine 01 Working!", LogStatus::INFO },
         { 105, "Double Machine 02 started processing", LogStatus::OK},
      };
   }
}

namespace LongDay {
   void UIManager::draw() {
      const auto& m  = machines.empty()  ? makeMockMachines()   : machines;
      const auto& c  = conveyors.empty() ? makeMockConveyors()  : conveyors;
      const auto& s  = machines.empty()  ? makeMockStats()      : stats;
      const auto& lg = logs.empty()      ? makeMockLogs()       : logs;

      // a window container, contains everything within one frame
      ImGuiIO& io = ImGui::GetIO();
      ImGui::SetNextWindowPos({ 0, 0 });
      ImGui::SetNextWindowSize(io.DisplaySize);
      ImGui::Begin("##host", nullptr,
         ImGuiWindowFlags_NoDecoration |
         ImGuiWindowFlags_NoMove       |
         ImGuiWindowFlags_NoBringToFrontOnFocus
      );
      
      TopbarView topbarView(state);
      StatsView statsView(s);
      PipelineView pipelineView(m, c, state.selectedStage, {1355, 300} );
      InspectorView inspectorView(m, state.selectedStage, {320, 300});
      LogPanelView logpanelView(lg, state, {-1.f, 130.f});

      topbarView.draw();
      ImGui::Spacing();
      statsView.draw();
      ImGui::Spacing();
      pipelineView.draw();
      ImGui::SameLine();
      inspectorView.draw();
      ImGui::Spacing();
      logpanelView.draw();
      

      // for(auto ui: views) {
      //    ui->draw();
      // }
      ImGui::End();
   }
}

