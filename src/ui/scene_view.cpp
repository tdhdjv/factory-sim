
#include "ui/ui_view.h"
#include "backend/scene.h"
#include "ui/ui_classes.h"
#include "ui/ui_data.h"

namespace LongDay{
   template<typename In, typename Out>
   class SceneView : public UIView{
      private:
      Scene<In, Out>& u_scene;
      PipelineView& u_sceneView;
      UIState& u_state;

      public:
      SceneView(Scene<In, Out>& scene, PipelineView& sceneView, UIState& state)
      : u_scene(scene), u_sceneView(sceneView), u_state(state) {};
      void draw() override {
      };
   };


}