
#pragma once
#include "ui/ui_data.h"
#include "backend/factory.h"

namespace LongDay{
	template <typename In, typename Out>
	class FactoryController{
		private:
			Factory<In, Out>& factory;

         std::vector<MachineDisplayData> u_machines;
         std::vector<ConveyorDisplayData> u_conveyors;
         FactoryStats u_stats;
         std::vector<LogEntry> u_logs;

		public:
         void sync_model();


         public:
         FactoryController();
         //void sync_data(UIState& state);

         const std::vector<MachineDisplayData>& getMachines()  const {return u_machines;};
         const std::vector<ConveyorDisplayData>& getConveyors()    const  {return u_conveyors;};
         const FactoryStats getStats() const {return u_stats;};
         const std::vector<LogEntry>& getLogs()  const{return u_logs;};
      };
}
