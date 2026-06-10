#include "log_view.h"
#include "core/logger.h"
#include "ui_color.h"
#include <imgui.h>

namespace LongDay {
	static ImVec4 color_for_status(LogStatus status){
	   switch(status){
		  case LogStatus::INFO:
			 return Colors::GREEN;
		  case LogStatus::WARN:
			 return Colors::YELLOW;
		  case LogStatus::ERROR:
			 return Colors::RED;
	   }
	   return Colors::GREEN;
	}
	void LogView::draw() {
		ImGui::BeginChild("OuterLogPanel", ImVec2(0, 0), true);

		ImGui::Text("Factory Log Entries");
		ImGui::SameLine(160.f);

		if(ImGui::Button("Clear Log")) {
		  Logger::clear();
		}
		ImGui::Separator();

		// Scrollable inner region 
		ImGui::BeginChild("LogScroll", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		for(const auto& log : Logger::get_logs()){
			ImGui::TextColored(color_for_status(log.status), "%s", log.message.c_str());
		}

		// Auto-scroll to bottom so newest entry is always visible
		if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
		 ImGui::SetScrollHereY(1.0f);
		}

		ImGui::EndChild();   // LogScroll
		ImGui::EndChild();   // LogPanelOuter
	}
}
