#pragma once

struct LongDayFactoryState {
   bool running = false;
   bool paused = false;

   bool requestTick = false;
   bool requestReset = false;

   int selectedStage = -1;

   float simulationSpeed = 1.0f;

};