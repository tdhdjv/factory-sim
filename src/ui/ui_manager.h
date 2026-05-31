#pragma once
#include "ui/ui_data.h"
#include "ui/ui_view.h"
#include <vector>
#include <memory>

namespace LongDay {
   class UIManager: public UIView {
      private:
         std::vector<std::unique_ptr<UIView>> views;

      public:
         void draw() override;
         void add_ui_view(std::unique_ptr<UIView> view);
   };
}



