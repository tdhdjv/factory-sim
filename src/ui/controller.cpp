#include "ui/controller.h"
#include "ui/ui_state.h"


LongDay::FactoryController::FactoryController(){
   u_factory.set_consumer(&u_sink);
};

void LongDay::FactoryController::update(LongDayFactoryState& state){

   if(state.requestStart){
      for(u32 i; i<10; i++) u_factory.feed();
      state.requestStart = false;
      state.running = true;
   };

   if(state.requestReset){
      state.tick = 0;
      state.running = false;
      
   };

   if(state.requestTick || state.running){

   };

   if(state.clearLog){

   };

};

