#include "ui/log_panel.h"
#include "ui/ui_colors.h"
#include <imgui.h>

static ImVec4 color_for_status(UI::LogStatus status){
   switch(status){
      case UI::LogStatus::INFO:
         return UI::Colors::PRIMARY;
      case UI::LogStatus::WARN:
         return UI::Colors::LOG_WARN;
      case UI::LogStatus::DANGER:
         return UI::Colors::BROKEN;
      case UI::LogStatus::OK:
         return UI::Colors::WORKING;
   }
   return UI::Colors::PRIMARY;
}

void LogPanel::draw() {

    // Outer child: fixed height panel with a header + clear button
    ImGui::BeginChild("LogPanelOuter", ImVec2(0, u_size.y > 0 ? u_size.y : 160.f), true);

    ImGui::Text("Factory Log Entries");
    ImGui::SameLine(ImGui::GetContentRegionAvail().x - 80.f);

    if (ImGui::Button("Clear Log")) {
        u_state.clearLog = true;
    }
    ImGui::Separator();

    // Scrollable inner region 
    ImGui::BeginChild("LogScroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for(const auto& log : u_logs){
         ImGui::TextColored(color_for_status(log.status), "[%u] %s", log.tick, log.message.c_str());
      }

    // Auto-scroll to bottom so newest entry is always visible
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
        ImGui::SetScrollHereY(1.0f);
    }

    ImGui::EndChild();   // LogScroll
    ImGui::EndChild();   // LogPanelOuter
}
