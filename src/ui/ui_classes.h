#pragma once 
#include <imgui.h>
#include "ui/ui_data.h"
#include "ui/ui_view.h"

namespace LongDay{

   class TopbarView : public UIView {
      private:
      UIState& u_state;
      public:
      TopbarView(UIState& state): u_state(state){};
      void draw() override;
   };

   class StatsView : public UIView {
      private:
       const FactoryStats& u_stats;
      public:
      StatsView(const FactoryStats& stats ): u_stats(stats){};
      void draw() override;
   };

   class InspectorView : public UIView{
      private:
      const std::vector<MachineDisplayData>& u_machines;
      i32& u_selectedMachine;
      ImVec2 u_size;
      public:
      InspectorView(const std::vector<MachineDisplayData>& machines, i32& selectedMachine, ImVec2 size):
      u_machines(machines), u_selectedMachine(selectedMachine), u_size(size){};
      void draw() override;
   };

   class PipelineView : public UIView {
      private:
      const std::vector<MachineDisplayData>& u_machines;
      const std::vector<ConveyorDisplayData>& u_conveyors;
      i32& u_selectedMachine;
      ImVec2 u_size;

      public:
      PipelineView(const std::vector<MachineDisplayData>& machines,
      const std::vector<ConveyorDisplayData>& conveyors,
      i32& selectedMachine, ImVec2 size): u_machines(machines), u_conveyors(conveyors), u_selectedMachine(selectedMachine), u_size(size) {};
      //void static draw_machine(const MachineDisplayData& machines, bool selected);
      void draw() override;
   };

   class LogPanelView : public UIView {
      private:
      const std::vector<LogEntry>& u_logs;
      UIState& u_state;
      ImVec2 u_size;
      public:
      LogPanelView(const std::vector<LogEntry>& logs, UIState& state, ImVec2 size): u_logs(logs), u_state(state), u_size(size){};
      void draw () override;
   };

};

