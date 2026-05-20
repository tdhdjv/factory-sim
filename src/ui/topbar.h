#pragma once

class LongDayFactory;
struct LongDayFactoryState;

//draws the control bar  [Start] [Pause] [Reset] Speed     CurrentTick
namespace TopbarPanel{

    // state      — reads running/paused flags; writes speed, requestTick,
    //              requestReset (UI sets flags; Controller acts on them)
    // currentTick — displayed as "Tick: 000"
    // scenarioNames — list shown in the Scenario dropdown
    // selectedScenario — index into scenarioNames; written by the dropdown
    void draw(LongDayFactoryState& state,
              u32 currentTick,
              const std::vector<std::string>& scenarioNames,
              int& selectedScenario);

};