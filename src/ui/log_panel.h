#pragma once
#include <imgui.h>
#include "ui/ui_data.h"

namespace LogPanel {
   void draw(const std::vector<UI::LogEntry>& logs, ImVec2 size);

}