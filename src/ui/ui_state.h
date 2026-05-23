#pragma once

struct LongDayFactoryState {
   bool running = false;
   bool paused = false;

   bool requestStart = false;
   bool requestReset = false;
   bool forceBreak = false;
   bool instantRepair = false;

   int selectedStage = -1;

   int simulationSpeed = 1;

   bool clearLog = false;
};