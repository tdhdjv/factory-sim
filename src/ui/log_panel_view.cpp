#include "ui/ui_classes.h"
#include "ui/ui_colors.h"
#include <imgui.h>

namespace LongDay { 
static ImVec4 color_for_status(LogStatus status){
   switch(status){
      case LogStatus::INFO:
         return Colors::PRIMARY;
      case LogStatus::WARN:
         return Colors::LOG_WARN;
      case LogStatus::DANGER:
         return Colors::BROKEN;
      case LogStatus::OK:
         return Colors::WORKING;
   }
   return Colors::PRIMARY;
   }
}

namespace LongDay{
   void LogPanelView::draw() {

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
   };

};