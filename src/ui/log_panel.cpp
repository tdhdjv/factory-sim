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


void LogPanel::draw(){
      ImGui::BeginChild("Factory Log Entries", ImVec2(0,0), true);
      ImGui::Text("Factory Log Entries");
      ImGui::SameLine(1650.f, 0.f);
      ImGui::Button("Clear Log");
      
      for(const auto& log : u_logs){
         ImGui::TextColored(color_for_status(log.status), "[%u] %s", log.tick, log.message.c_str());
      }
      
      ImGui::EndChild();
   };

