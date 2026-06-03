#pragma once
#include "ui/ui_view.h"
#include "ui/ui_classes.h"
#include "ui/scene_view.h"
#include "backend/scene.h"
#include "long_day_factory/hope_and_dreams.h"
#include "long_day_factory/day.h"

namespace LongDay {

   class UIManager : public UIView {
   private:
      UIState& u_state;
      TopbarView u_topbar;
      SceneView  u_sceneView;

   public:
      UIManager(Scene<HopeAndDreams, Day>& scene, UIState& state);
      void draw() override;
   };

}
