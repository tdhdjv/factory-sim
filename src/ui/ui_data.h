#pragma once
#include <string>
#include <vector>
#include <define.h>

namespace UI {

   enum struct MachineState {
      IDLE,
      WORKING,
      BROKEN,
      MAINTENANCE
   };

   // [Machine] 
   // [State] -> WORKING
   // [Health] -> 100%
   // [Progress] -> 25%
   // [Queue] ->  4/5
   // [Output] -> 4
   // [Process Time] -> 4 ticks
   struct MachineDisplayData {
      std::string id;    
      std::string label;  
      MachineState state; 
      float health;  
      float progress;
      u64 queueSize;
      u64 queueCapacity;
      u64 outputCount;
      u32 processTimeTicks;  
   };

   
   struct ConveyorDisplayData {
      std::string id;
      std::string label; 
      u64 itemCount;
      u64 capacity;
      float fillPercent;
   };

   enum struct LogStatus {
      INFO,
      WARN,
      DANGER,
      OK 
   };

   struct LogEntry{
      u32 tick;
      std::string message;
      LogStatus status;
   };

   // Stats [FINISHED] [IN PROGRESS] [BREAKDOWNS] [LOST]
   struct FactoryStats{
      u32 finished = 0;
      u32 inProgress = 0;
      u32 breakDowns = 0;
      u32 lost = 0;
   };
};
