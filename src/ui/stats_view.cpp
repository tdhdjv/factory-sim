#include "ui/ui_classes.h"
#include "ui/ui_colors.h"
#include <imgui.h>

namespace LongDay{

   static void draw_card( const char* label, u32 value, ImVec4 valueColor) {
      ImGui::PushStyleColor(ImGuiCol_ChildBg, Colors::BG_PRIMARY);
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

   void StatsView::draw(){

      draw_card("FINISHED", u_stats.finished, Colors::WORKING);
      ImGui::SameLine();
      draw_card("IN PROGRESS", u_stats.inProgress, Colors::PRODUCT_DOT);
      ImGui::SameLine();
      draw_card("BREAKDOWNS", u_stats.breakDowns, Colors::BROKEN);
      ImGui::SameLine();
      draw_card("LOST", u_stats.lost, Colors::LOG_WARN);

   };
};