#include "ui/controller.h"
#include "ui/ui_state.h"
#include <iostream>


LongDay::FactoryController::FactoryController(){
   u_factory.set_consumer(&u_sink);
};

void LongDay::FactoryController::update(LongDayFactoryState& state){

   if(state.requestStart){
      for(u32 i = 0; i<10; i++) u_factory.feed();
      state.requestStart = false;
      state.running = true;
   };

   if(state.requestReset){
      state.tick = 0;
      state.running = false;
      state.requestReset = false;
      u_logs.clear();
      
   };

   if(state.requestTick || state.running){
      for (u32 i = 0; i< state.simulationSpeed; i++) {
         u_factory.tick();
         state.tick++;
      }
      if (!state.running) state.requestTick = false;
   };

   if(state.clearLog){
      u_logs.clear();
      state.clearLog = false;
   };

   synkDisplaydata(state.tick);
};

