#pragma once
#include "ui/ui_view.h"
#include "ui/ui_classes.h"
#include "ui/controller.h"

namespace LongDay {

   class UIManager : public UIView {
   private:
      FactoryController& u_controller;
      FactoryState&      u_state;

      TopbarView    u_topbar;
      StatsView     u_stats;
      PipelineView  u_pipeline;
      InspectorView u_inspector;
      LogPanelView  u_logPanel;

   public:
      UIManager(FactoryController& controller, FactoryState& state);
      void draw() override;
   };

}

// std::vector<std::unique_ptr<UIView>> views;
// void add_ui_view(std::unique_ptr<UIView> view);
 



