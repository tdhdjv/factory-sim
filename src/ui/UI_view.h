#pragma once
#include<iostream>

namespace LongDay {
   class UI_view {
      private:
      UI_controller* controller;
      public:
      virtual void draw() = 0;
   };

   class UI_controller {
      public:
      virtual void update() = 0;
   }
};