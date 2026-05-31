#pragma once
#include <string>
#include <vector>
#include <define.h>

namespace LongDay {

   enum struct MachineState {
      IDLE,
      WORKING,
      BROKEN,
      MAINTENANCE
   };

   struct MachineDisplayData {
      std::string id;    
      std::string label;  
      MachineState state; 
      f32 health;  
      f32 progress;
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

   struct FactoryState {
   bool running = false;
   bool paused = false;

   bool requestStart = false;
   bool requestReset = false;
   bool forceBreak = false;
   bool instantRepair = false;

   bool requestTick = false;
   int tick = 0;
   int selectedStage = -1;
   int simulationSpeed = 1;

   bool clearLog = false;
   };

};
