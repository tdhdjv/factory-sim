#pragma once
#include "ui/ui_state.h"
#include "ui/UI_view.h"

class Topbar : public LongDay::UI_view{
   private:
   LongDayFactoryState& u_state;
   public:
   Topbar(LongDayFactoryState& state): u_state(state){};
   void draw() override;
};


