#include "ui/stats_row.h"
#include "ui/ui_colors.h"
#include <imgui.h>

namespace StatsRow {
   static void draw_card(const char* label, u32 value, ImVec4 valueColor);

   void draw(const UI::FactoryStats& stats){
      draw_card("FINISHED", stats.finished, UI::Colors::WORKING);
      ImGui::SameLine(0, 4);

      draw_card("IN PROGRESS", stats.inProgress, UI::Colors::PRODUCT_DOT);
      ImGui::SameLine(0,4);

      draw_card("BREAKDOWNS", stats.breakDowns, UI::Colors::BROKEN);
      ImGui::SameLine(0, 4);

      draw_card("LOST", stats.lost, UI::Colors::LOG_WARN);
      ImGui::SameLine(0, 4);
   }

}