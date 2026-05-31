#pragma once
#include<iostream>

namespace LongDay {
   class UIView {
      public:
      virtual ~UIView() = default;
      virtual void draw() = 0;
   };
};