
#include "ui/ui_view.h"
#include "backend/scene.h"
#include "ui/ui_classes.h"
#include "ui/ui_data.h"
#include "ui/ui_manager.h"

namespace LongDay{
   template<typename In, typename Out>
   class SceneView : public UIView{
      private:
      Scene<In, Out>& u_scene;
      UIState& u_state;
      
      std::vector<MachineDisplayData> u_machines;
      std::vector<ConveyorDisplayData> u_conveyors;
      FactoryStats u_stats;
      std::vector<LogEntry> u_logs;

      PipelineView u_pipelineView;
      InspectorView u_inspectorView;
      StatsView u_statsView;
      LogPanelView u_logPanelView;
      

      public:
      SceneView(Scene<In, Out>& scene, UIState& state)
      : u_scene(scene), u_state(state),
        u_pipelineView(u_machines, u_conveyors, state.selectedStage, {1355, 300}),
        u_inspectorView(u_machines, state.selectedStage, {320, 300}), 
        u_statsView(u_stats),
        u_logPanelView(u_logs, state, {-1.f, 130.f})
        {};
      void draw() override {
         syncDisplayData();//read backend -> fill vectors

         u_statsView.draw();
         ImGui::Spacing();
         u_pipelineView.draw();
         ImGui::SameLine();
         u_inspectorView.draw();
         ImGui::Spacing();
         u_logPanelView.draw();


      };
   };


}