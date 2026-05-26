#include "ui/stats_row.h"
#include "ui/ui_colors.h"
#include <imgui.h>


static void draw_card( const char* label, u32 value, ImVec4 valueColor) {
   
   ImGui::PushStyleColor(ImGuiCol_ChildBg, UI::Colors::BG_PRIMARY);
   ImGui::BeginChild(label, ImVec2(170, 90), true);
   ImGui::TextUnformatted(label);

   ImGui::Separator();

   ImGui::PushStyleColor(ImGuiCol_Text, valueColor);
   ImGui::SetWindowFontScale(1.5f);
   ImGui::Text("%u", value);

   ImGui::SetWindowFontScale(1.0f);
   ImGui::PopStyleColor();
   ImGui::EndChild();
   ImGui::PopStyleColor();
}


void StatsRow::draw(){

   draw_card("FINISHED", u_stats.finished, UI::Colors::WORKING);
   ImGui::SameLine();
   draw_card("IN PROGRESS", u_stats.inProgress, UI::Colors::PRODUCT_DOT);
   ImGui::SameLine();
   draw_card("BREAKDOWNS", u_stats.breakDowns, UI::Colors::BROKEN);
   ImGui::SameLine();
   draw_card("LOST", u_stats.lost, UI::Colors::LOG_WARN);

}

