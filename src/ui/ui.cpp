#include "ui/ui.h"
#include "ui/ui_colors.h"
#include "ui/topbar.h"
#include "ui/stats_row.h"
#include "ui/factory_canvas.h"
#include "ui/inspector.h"
#include "ui/log_panel.h"
#include <imgui.h>

// Temporary data, the real data will be included during integration
namespace {
   
   std::vector<UI::MachineDisplayData> makeMockMachines() {
      return {
         { "m1", "Double Machine 01",    UI::MachineState::WORKING,     92.f, 0.60f, 3, 5, 17, 3 },
         { "m2", "Double Machine 02", UI::MachineState::IDLE,        100.f, 0.00f, 0, 5, 12, 5 },
         { "m3", "Double Machine 03",   UI::MachineState::BROKEN,      20.f, 0.00f, 1, 5, 8,  4 },
      };
   }

   std::vector<UI::ConveyorDisplayData> makeMockConveyors() {
      return {
         { "c1", "C1", 2, 5, 0.4f },
         { "c2", "C2", 1, 5, 0.2f },
      };
   }

   UI::FactoryStats makeMockStats() {
      return { 31, 4, 1, 0 };
   }

   std::vector<UI::LogEntry> makeMockLogs() {
      return {
         { 125, "Double MAchine 01 BROKEN!",           UI::LogStatus::DANGER },
         { 122, "Double MAchine 02 started processing", UI::LogStatus::INFO   },
         { 120, "Double Machine 03 finished LongDay",   UI::LogStatus::OK     },
      };
   }

} 


namespace FactoryUI {

   void draw(
      LongDayFactoryState&                        state,
      const std::vector<UI::MachineDisplayData>&  machines,
      const std::vector<UI::ConveyorDisplayData>& conveyors,
      const UI::FactoryStats&                     stats,
      const std::vector<UI::LogEntry>&            logs
   ){
      
      const auto& m  = machines.empty()  ? makeMockMachines()   : machines;
      const auto& c  = conveyors.empty() ? makeMockConveyors()  : conveyors;
      const auto& s  = machines.empty()  ? makeMockStats()      : stats;
      const auto& lg = logs.empty()      ? makeMockLogs()       : logs;

      // ── One fullscreen host window ─────────────────────────────────
      // This is NOT a visible window — it's just a container so all
      // panels are anchored to the screen instead of floating freely.
      ImGuiIO& io = ImGui::GetIO();
      ImGui::SetNextWindowPos({ 0, 0 });
      ImGui::SetNextWindowSize(io.DisplaySize);
      ImGui::Begin("##host", nullptr,
         ImGuiWindowFlags_NoDecoration |
         ImGuiWindowFlags_NoMove       |
         ImGuiWindowFlags_NoBringToFrontOnFocus
      );

      Topbar::draw(state);
      ImGui::Spacing();

      StatsRow::draw(s);
      ImGui::Spacing();

      float inspW   = 220.f;
      float panelH  = 300.f;
      float canvasW = ImGui::GetContentRegionAvail().x - inspW - ImGui::GetStyle().ItemSpacing.x;

      FactoryCanvas::draw(m, c, state.selectedStage, {1355, 300 });
      ImGui::SameLine();
      Inspector::draw(m, state.selectedStage, { 320, 300 });

      ImGui::Spacing();
      LogPanel::draw(lg, { -1.f, 130.f });

      ImGui::End();
   }

} 