#pragma once
#include <string>
#include <vector>
#include <define.h>

namespace LongDay {

   enum MachineState {
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
      f32 fillPercent;
   };

   enum LogStatus {
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

   struct UIState {
		 b8 running = false;
		 b8 paused = false;
		 b8 requestStart = false;
		 b8 requestReset = false;
		 b8 forceBreak = false;
		 b8 instantRepair = false;
		 b8 requestTick = false;
		 i32 tick = 0;
		 i32 selectedStage = -1;
		 i32 simulationSpeed = 1;

		 b8 clearLog = false;
   };

};
