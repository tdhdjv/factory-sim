#include "ui/ui.h"

#include "ui/topbar.h"
#include "ui/stats_row.h"
#include "ui/factory_canvas.h"
#include "ui/inspector.h"
#include "ui/log_panel.h"

#include <imgui.h>

namespace {

std::vector<UI::MachineDisplayData> mockMachines(){

   return {
      {
         "m1",
         "Input",
         UI::MachineState::WORKING,
         100.f,
         0.25f,
         2,
         5,
         20,
         2
      },
      {
         "m2",
         "Cutter",
         UI::MachineState::WORKING,
         92.f,
         0.75f,
         4,
         5,
         17,
         4
      },
      {
         "m3",
         "Painter",
         UI::MachineState::IDLE,
         100.f,
         0.10f,
         1,
         5,
         11,
         3
      },
      {
         "m4",
         "Output",
         UI::MachineState::WORKING,
         100.f,
         1.0f,
         0,
         5,
         31,
         1
      }
   };
}

UI::FactoryStats mockStats(){

   UI::FactoryStats stats;

   stats.finished = 31;
   stats.inProgress = 7;
   stats.breakDowns = 1;
   stats.lost = 0;

   return stats;
}

std::vector<UI::LogEntry> mockLogs(){

   return {
      {
         120,
         "Cutter processed Iron Plate",
         UI::LogStatus::OK
      },

      {
         122,
         "Painter started processing",
         UI::LogStatus::INFO
      },

      {
         125,
         "Conveyor overload detected",
         UI::LogStatus::WARN
      }
   };
}

}

void LongDayFactoryUI::draw(
   LongDayFactory& factory,
   LongDayFactoryState& state
){
   static int selectedMachine = -1;

   auto machines = mockMachines();

   auto stats = mockStats();

   auto logs = mockLogs();

   Topbar::draw();

   StatsRow::draw(stats);

   FactoryCanvas::draw(
      machines,
      selectedMachine
   );

   Inspector::draw(
      machines,
      selectedMachine
   );
   LogPanel::draw(logs);
}