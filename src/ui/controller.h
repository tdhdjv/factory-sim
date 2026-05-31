#pragma once
#include "ui/ui_data.h"
//#include "backend/test.h"

namespace LongDay{
   class FactoryController{
         private:
//         LongDay::LongDayFactory u_factory;
//         LongDay::PrintI32Sink u_sink;

         std::vector<MachineDisplayData> u_machines;
         std::vector<ConveyorDisplayData> u_conveyors;
         FactoryStats u_stats;
         std::vector<LogEntry> u_logs;

         void syncDisplaydata(int tick);//reads backend and fills the u_machines etc.


         public:
         FactoryController();
         void update(FactoryState& state);

         const std::vector<MachineDisplayData>& getMachines()  const {return u_machines;};
         const std::vector<ConveyorDisplayData>& getConveyors()    const  {return u_conveyors;};
         const FactoryStats getStats() const {return u_stats;};
         const std::vector<LogEntry>& getLogs()  const{return u_logs;};
      };
}
