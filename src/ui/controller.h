#pragma once
#include "ui/ui_state.h"
#include "ui/ui_data.h"
#include "backend/test.h"

namespace LongDay{
   class FactoryController{
         private:
         LongDay::LongDayFactory u_factory;
         LongDay::PrintI32Sink u_sink;

         std::vector<UI::MachineDisplayData> u_machines;
         std::vector<UI::ConveyorDisplayData> u_conveyors;
         UI::FactoryStats u_stats;
         std::vector<UI::LogEntry> u_logs;

         void synkDisplaydata(int tick);//reads backend and fills the u_machines etc.


         public:
         FactoryController();
         void update(LongDayFactoryState& state);

         const std::vector<UI::MachineDisplayData>& getMachines()  const {return u_machines;};
         const std::vector<UI::ConveyorDisplayData>& getConveyors()    const  {return u_conveyors;};
         const UI::FactoryStats getStats() const {return u_stats;};
         const std::vector<UI::LogEntry>& getLogs()  const{return u_logs;};

      };
}