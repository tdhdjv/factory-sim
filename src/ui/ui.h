#pragma once
#include "ui/ui.cpp"

class LongDayFactory;
struct LongDayFactoryState;

class LongDayFactoryUI{
   public:
      static void draw(LongDayFactory& factory, LongDayFactoryState& state);
};



