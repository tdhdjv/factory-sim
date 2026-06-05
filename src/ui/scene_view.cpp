#include "ui/scene_view.h"
#include "backend/machine_base.h"
#include "backend/conveyor.h"
#include <imgui.h>
#include<map>

namespace LongDay {

    SceneView::SceneView(Scene<HopeAndDreams, Day>& scene, UIState& state)
        : u_scene(scene),
          u_state(state),
          u_statsView(u_stats),
          u_pipelineView(u_machines, u_conveyors, state.selectedStage, {1355, 300}),
          u_inspectorView(u_machines, state.selectedStage, {320, 300}),
          u_logPanelView(u_logs, state, {-1.f, 0.f})
    {}

   
    // applyStateToBackend, translate button/combo events into backend calls
    void SceneView::applyStateToBackend() {
        // Scenario selector, enable/disable breakdown mode
        bool wantBreakdowns = (u_state.scenario == BREAKDOWN);
        if (wantBreakdowns != u_scene.is_breakdown_mode()) {
            u_scene.set_breakdown_mode(wantBreakdowns);
            u_logs.push_back({ u_tick,
                wantBreakdowns ? "Scenario: Random Breakdowns mode enabled"
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

        // Ticks
        if (u_state.running || u_state.requestTick) {
            u32 steps = u_state.running ? (u32)u_state.simulationSpeed : 1u;
            for (u32 i = 0; i < steps; i++) {
                u_scene.tick();
                u_tick++;
            }
            u_state.tick = (i32)u_tick;
            if (!u_state.running) u_state.requestTick = false;
        }

        // Pause 
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

   
    // syncDisplayData reads backend and fills machines
    void SceneView::syncDisplayData() {
        auto* factory = u_scene.get_factory();
        const auto& stages = factory->get_stages();

        u_machines.clear();
        u_conveyors.clear();

        u32 machineIdx = 0;
        u32 conveyorIdx = 0;

        for (const auto& stagePtr : stages) {
            StageBase* base = stagePtr.get();

            // Machines
            if (auto* m = dynamic_cast<MachineBase*>(base)) {
                MachineDisplayData mdd;
                mdd.id    = std::string("m") + std::to_string(machineIdx);
                mdd.label = base->get_name();

                // Determine state
                if (m->is_broken()) {
                    mdd.state = MachineState::BROKEN;
                } else {
                    mdd.state = MachineState::IDLE; }

                // Queue info — we need to cast to an AtomicStage to read queue
                // We use the AtomicStageAccessor interface
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
                    ? (f32)m->get_progress() / (f32)ticks : 0.f;
                mdd.health      = m->is_broken() ? 0.f : 100.f;
                mdd.outputCount = m->get_output_count();


                // Track previous machine state so we can detect transitions
                // We use a persistent map keyed by machine id
                static std::map<std::string, u64> prevOutputCount;
                static std::map<std::string, bool> prevBroken;

                bool wasBroken = prevBroken.count(mdd.id) ? prevBroken[mdd.id] : false;

                // Log new breakdowns (transition: not broken → broken)
                if (m->is_broken() && !wasBroken) {
                    u_logs.push_back({ u_tick,  mdd.label + " BROKEN!", LogStatus::DANGER });
                }

                // Log repair (transition: broken → working)
                if (!m->is_broken() && wasBroken) {
                    u_logs.push_back({ u_tick, mdd.label + " repaired and back online.", LogStatus::OK });
                }

                // Log each new output (machine finished processing a product)
                u64 prevOut = prevOutputCount.count(mdd.id) ? prevOutputCount[mdd.id] : 0;
                if (mdd.outputCount > prevOut) {
                    u64 delta = mdd.outputCount - prevOut;
                    for (u64 i = 0; i < delta; i++) {
                        u_logs.push_back({ u_tick, mdd.label + " finished processing a product. (output #"
                            + std::to_string(prevOut + i + 1) + ")",
                            LogStatus::OK });
                    }
                }

                // Log when machine actively consumes from its queue
                if (!m->is_broken() && mdd.queueSize > 0 && mdd.state == MachineState::WORKING) {
                    static std::map<std::string, u64> prevQueueSize;
                    u64 prevQ = prevQueueSize.count(mdd.id) ? prevQueueSize[mdd.id] : mdd.queueSize;
                    if (prevQ > mdd.queueSize) {
                        // queue shrank → item was consumed
                        u_logs.push_back({ u_tick,
                            mdd.label + " consumed an item from queue. (queue: "
                            + std::to_string(mdd.queueSize) + "/" + std::to_string(mdd.queueCapacity) + ")",
                            LogStatus::INFO });
                    }
                    prevQueueSize[mdd.id] = mdd.queueSize;
                }

                prevBroken[mdd.id]      = m->is_broken();
                prevOutputCount[mdd.id] = mdd.outputCount;

                u_machines.push_back(mdd);
                machineIdx++;
            }
            // Conveyor 
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
