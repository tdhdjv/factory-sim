#include "ui/scene_view.h"
#include "backend/machine_base.h"
#include "backend/conveyor.h"
#include <imgui.h>

namespace LongDay {

    // -------------------------------------------------------------------------
    // Constructor — sub-views hold const refs into our buffers, so the buffers
    // must be constructed before the sub-views.  Member initialiser order in
    // the class definition already guarantees this because the buffers are
    // declared first.
    // -------------------------------------------------------------------------
    SceneView::SceneView(Scene<HopeAndDreams, Day>& scene, UIState& state)
        : u_scene(scene),
          u_state(state),
          u_statsView(u_stats),
          u_pipelineView(u_machines, u_conveyors, state.selectedStage, {1355, 300}),
          u_inspectorView(u_machines, state.selectedStage, {320, 300}),
          u_logPanelView(u_logs, state, {-1.f, 130.f})
    {}

    // -------------------------------------------------------------------------
    // applyStateToBackend  — translate button/combo events into backend calls
    // -------------------------------------------------------------------------
    void SceneView::applyStateToBackend() {
        // Scenario selector → enable/disable breakdown mode
        bool wantBreakdowns = (u_state.scenario == BREAKDOWN);
        if (wantBreakdowns != u_scene.is_breakdown_mode()) {
            u_scene.set_breakdown_mode(wantBreakdowns);
            u_logs.push_back({ u_tick,
                wantBreakdowns ? "Scenario: BREAKDOWN mode enabled"
                               : "Scenario: Normal flow restored",
                wantBreakdowns ? LogStatus::WARN : LogStatus::OK });
        }

        // Reset clears everything
        if (u_state.requestReset) {
            u_tick = 0;
            u_stats = {};
            u_logs.clear();
            u_state.requestReset = false;
            u_state.running      = false;
        }

        // Start
        if (u_state.requestStart) {
            u_state.running      = true;
            u_state.requestStart = false;
        }

        // Advance ticks
        if (u_state.running || u_state.requestTick) {
            u32 steps = u_state.running ? (u32)u_state.simulationSpeed : 1u;
            for (u32 i = 0; i < steps; i++) {
                u_scene.tick();
                u_tick++;
            }
            u_state.tick = (i32)u_tick;
            if (!u_state.running) u_state.requestTick = false;
        }

        // Pause just flips the running flag
        if (u_state.paused) {
            u_state.running = false;
            u_state.paused  = false;
        }

        // Clear log
        if (u_state.clearLog) {
            u_logs.clear();
            u_state.clearLog = false;
        }
    }

    // -------------------------------------------------------------------------
    // syncDisplayData  — read live backend state → fill display buffers
    // -------------------------------------------------------------------------
    void SceneView::syncDisplayData() {
        auto* factory = u_scene.get_factory();
        const auto& stages = factory->get_stages();

        u_machines.clear();
        u_conveyors.clear();

        u32 machineIdx = 0;
        u32 conveyorIdx = 0;

        for (const auto& stagePtr : stages) {
            StageBase* base = stagePtr.get();

            // --- Machine ---
            if (auto* m = dynamic_cast<MachineBase*>(base)) {
                MachineDisplayData mdd;
                mdd.id    = std::string("m") + std::to_string(machineIdx);
                mdd.label = base->get_name();

                // Determine state
                if (m->is_broken()) {
                    mdd.state = MachineState::BROKEN;
                } else {
                    // Cast to AtomicStageBase to get queue info
                    // We use a small helper: try casting to AtomicStage<?,?> via
                    // a non-template base we add to AtomicStage.
                    // For now we get size/capacity via MachineBase helpers
                    // (we'll try a dynamic_cast trick below).
                    mdd.state = MachineState::IDLE; // default; override below
                }

                // Queue info — we need to cast to an AtomicStage to read queue
                // We use the AtomicStageAccessor interface (see stage.h additions)
                if (auto* atomic = dynamic_cast<AtomicStageAccessor*>(base)) {
                    mdd.queueSize     = atomic->get_size();
                    mdd.queueCapacity = atomic->get_capacity();
                    if (!m->is_broken() && mdd.queueSize > 0)
                        mdd.state = MachineState::WORKING;
                } else {
                    mdd.queueSize     = 0;
                    mdd.queueCapacity = 0;
                }

                u32 ticks = m->get_ticks_for_production();
                mdd.processTimeTicks = ticks;
                mdd.progress = (ticks > 0)
                    ? (float)m->get_progress() / (float)ticks
                    : 0.f;

                // health: 100% when not broken, 0% when broken (simple model)
                mdd.health      = m->is_broken() ? 0.f : 100.f;
                mdd.outputCount = m->get_output_count();

                // Log new breakdowns
                if (m->is_broken() && mdd.state == MachineState::BROKEN) {
                    // Only log once per breakdown — check last log
                    bool alreadyLogged = false;
                    if (!u_logs.empty()) {
                        const auto& last = u_logs.back();
                        alreadyLogged = (last.message.find(mdd.label) != std::string::npos
                                         && last.status == LogStatus::DANGER);
                    }
                    if (!alreadyLogged) {
                        u_logs.push_back({ u_tick,
                            mdd.label + " BROKEN!",
                            LogStatus::DANGER });
                    }
                }

                u_machines.push_back(mdd);
                machineIdx++;
            }
            // --- Conveyor ---
            else if (auto* atomic = dynamic_cast<AtomicStageAccessor*>(base)) {
                ConveyorDisplayData cdd;
                cdd.id          = std::string("c") + std::to_string(conveyorIdx);
                cdd.label       = base->get_name();
                cdd.itemCount   = atomic->get_size();
                cdd.capacity    = atomic->get_capacity();
                cdd.fillPercent = atomic->get_fill();
                u_conveyors.push_back(cdd);
                conveyorIdx++;
            }
        }

        // Stats: count broken machines, total in-progress items across conveyors
        u_stats.breakDowns  = 0;
        u_stats.inProgress  = 0;
        for (const auto& m : u_machines) {
            if (m.state == MachineState::BROKEN) u_stats.breakDowns++;
            u_stats.inProgress += (u32)m.queueSize;
        }
        for (const auto& c : u_conveyors) {
            u_stats.inProgress += (u32)c.itemCount;
        }
        // finished = sum of machine output counts
        u_stats.finished = 0;
        for (const auto& m : u_machines) {
            u_stats.finished += (u32)m.outputCount;
        }
    }

    // -------------------------------------------------------------------------
    // draw
    // -------------------------------------------------------------------------
    void SceneView::draw() {
        applyStateToBackend();
        syncDisplayData();

        u_statsView.draw();
        ImGui::Spacing();
        u_pipelineView.draw();
        ImGui::SameLine();
        u_inspectorView.draw();
        ImGui::Spacing();
        u_logPanelView.draw();
    }

}
