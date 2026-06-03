#pragma once
#include "ui/ui_view.h"
#include "ui/ui_classes.h"
#include "ui/ui_data.h"
#include "backend/scene.h"
#include "long_day_factory/hope_and_dreams.h"
#include "long_day_factory/day.h"

namespace LongDay {

    // SceneView owns all sub-views and drives them from live Scene data.
    // It translates the backend Scene<In,Out> into display data structs,
    // then delegates rendering to the existing sub-views.
    class SceneView : public UIView {
    private:
        Scene<HopeAndDreams, Day>& u_scene;
        UIState& u_state;
        u32 u_tick = 0;

        // Display data buffers (owned here, sub-views hold const refs)
        std::vector<MachineDisplayData>  u_machines;
        std::vector<ConveyorDisplayData> u_conveyors;
        FactoryStats                     u_stats;
        std::vector<LogEntry>            u_logs;

        // Sub-views
        StatsView     u_statsView;
        PipelineView  u_pipelineView;
        InspectorView u_inspectorView;
        LogPanelView  u_logPanelView;

        // Fills display-data buffers from the live backend
        void syncDisplayData();

        // Applies UIState flags to the backend (start/stop/reset/scenario)
        void applyStateToBackend();

    public:
        SceneView(Scene<HopeAndDreams, Day>& scene, UIState& state);
        void draw() override;
    };

}
