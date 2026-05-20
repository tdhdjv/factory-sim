#pragma once

#include "ui/ui_data.h"

namespace FactoryCanvas {

void draw(
   const std::vector<UI::MachineDisplayData>& machines,
   int& selectedMachine
);

}