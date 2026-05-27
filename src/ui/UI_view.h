#pragma once
#include<iostream>


namespace LongDay {
   class UI_view {
      public:
      virtual ~UI_view() = default;
      virtual void draw() = 0;
   };

};