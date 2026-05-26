#pragma once
#include <imgui.h>
#include "ui/ui_data.h"
#include "ui/UI_view.h"

class LogPanel : public LongDay::UI_view{
   private:
   const std::vector<UI::LogEntry>& u_logs;
   ImVec2 u_size;
   public:
   LogPanel(const std::vector<UI::LogEntry>& logs, ImVec2 size): u_logs(logs), u_size(size){};
   void draw () override;
};
