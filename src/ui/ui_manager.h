#pragma once
#include "ui/ui_data.h"
#include "ui/ui_view.h"
#include <vector>
#include <memory>

namespace LongDay {
   class UIManager : UIView{
      private:
         FactoryState& u_state;
         std::vector<MachineDisplayData>& u_machines; 
         std::vector<ConveyorDisplayData>& u_conveyors;
         std::vector<LogEntry>& u_logs;
         FactoryStats& u_stats;
      
      
      // std::vector<std::unique_ptr<UIView>> views;

      public:
         UIManager(FactoryState& state, std::vector<MachineDisplayData>& machines,
         std::vector<ConveyorDisplayData>& conveyors, std::vector<LogEntry>& logs,
         FactoryStats& stats): u_state(state), u_machines(machines), u_conveyors(conveyors), u_logs(logs), u_stats(stats) {};
         void draw() override;
         // void add_ui_view(std::unique_ptr<UIView> view);
   };
}





