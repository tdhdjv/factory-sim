#pragma once
#include "ui/ui_data.h"
#include <vector>

namespace FactoryCanvas {

  // machines       — list of all machine display data (order = visual order)
    // conveyors      — list of conveyor display data
    // layouts        — SVG-unit positions for each machine (keyed by machineId)
    // selectedId     — id of the currently selected machine ("" = none)
    //                  Written when the user clicks a machine box.
    void draw(const std::vector<UI::MachineDisplayData>& machines,
              const std::vector<UI::ConveyorDisplayData>& conveyors,
              const std::vector<UI::MachineLayout>& layouts,
              std::string& selectedId);
               
}