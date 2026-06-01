#pragma once
#include "ui/ui_view.h"
#include "ui/ui_classes.h"
#include "ui/factory_controller.h"

namespace LongDay {

   class UIManager : public UIView {
   private:
      FactoryController& u_controller;
      UIState&      u_state;

      TopbarView    u_topbar;
      StatsView     u_stats;
      PipelineView  u_pipeline;
      InspectorView u_inspector;
      LogPanelView  u_logPanel;

   public:
      UIManager(FactoryController& controller, UIState& state);
      void draw() override;
   };

}

// std::vector<std::unique_ptr<UIView>> views;
// void add_ui_view(std::unique_ptr<UIView> view);
 



