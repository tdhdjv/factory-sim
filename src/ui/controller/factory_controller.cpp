#include "ui/controller/factory_controller.h"
#include "ui/ui_data.h"
#include <iostream>

namespace LongDay{
   FactoryController::FactoryController(){
   // u_factory.set_consumer(&u_sink);
   };

   void FactoryController::update(UIState& state){

      /*
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

      syncDisplaydata(state.tick);
      */
   };

   void FactoryController::syncDisplaydata(int tick) {
      
   };

};
