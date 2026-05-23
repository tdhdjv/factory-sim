#include "ui/log_panel.h"
#include "ui/ui_colors.h"

#include <imgui.h>

namespace LogPanel {
   
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

   void draw(const std::vector<UI::LogEntry>& logs, ImVec2 size){
      ImGui::BeginChild("Factory Log Enties", ImVec2(0,0), true);
      
      for(const auto& log : logs){
         ImGui::TextColored(color_for_status(log.status), "[%u] %s", log.tick, log.message.c_str());
      }
      
      ImGui::EndChild();
   }

}