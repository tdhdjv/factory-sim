#pragma once
#include "ui/ui_data.h"
#include "ui/UI_view.h"

class StatsRow : public LongDay::UI_view{
   private:
   const UI::FactoryStats& u_stats;
   public:
   StatsRow(const UI::FactoryStats& stats ): u_stats(stats){};
   void draw() override;
};
