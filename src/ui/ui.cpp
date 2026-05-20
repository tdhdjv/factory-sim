#include "ui/ui.h"
#include "backend/factory.h"
#include "ui/ui_state.h"

#include "ui/conveyor_list.h"
#include "ui/machine_list.h"
#include "ui/stats_row.h"
#include "ui/topbar.h"
#include "ui/inspector.h"


void LongDayFactoryUI::draw(LongDayFactory& factory, LongDayFactoryState& state){
    TopbarPanel::draw(factory, state);
    PipelinePanel::draw(factory, state);
    StatsRow::draw(factory);
    LogPanel::draw();

};






// namespace LongDay {
// namespace UI {

// // ── Shared state ──────────────────────────────────────────────────
// static int  s_tick       = 0; //counts how many ticks happened in total
// static bool s_running    = false; //by default paused, when pressing Start is becomes true
// static float s_speed     = 1.0f;   // ticks per second
// static float s_timer     = 0.0f; // counts time from the start of the process to the end
// static int  s_finished   = 0; //counts finished products
// static int  s_inProgress = 0; // counts products that are in process
// static int  s_selectedIdx = -1;    // which machine card is selected

// struct LogEntry {
//     int  tick;
//     std::string msg; // message
//     ImVec4 color;
// };
// static std::deque<LogEntry> s_log;

// static void push_log(const char* msg, ImVec4 color) {
//     s_log.push_front({ s_tick, msg, color });
//     if (s_log.size() > 64) s_log.pop_back();
// }

// // ── Colors ────────────────────────────────────────────────────────
// static ImVec4 COL_GREEN  = { 0.18f, 0.80f, 0.44f, 1.f }; // ImVec4 holds 4 colors, and instead of writing numbers each time 
//                                                          //we use a convenient way by making variables that store particular colors
// static ImVec4 COL_AMBER  = { 0.95f, 0.61f, 0.07f, 1.f };
// static ImVec4 COL_RED    = { 0.91f, 0.30f, 0.24f, 1.f };
// static ImVec4 COL_BLUE   = { 0.20f, 0.60f, 0.86f, 1.f }; 
// static ImVec4 COL_DIM    = { 0.47f, 0.51f, 0.58f, 1.f };

// //makes ticks, takes const ref to atomic stages cuz we don't modify or make copies of stages, so it should be const
// static void do_tick(const std::vector<AtomicStage<int,int>*>& stages) {
//     s_tick++; // incrments global tick counter
//     for (int i = (int)stages.size()-1; i >= 0; i--)
//         stages[i]->tick(); // ticks are in reverse order because we need to be able to wait until the item is pushed to 
//                           //the next stage before pushing the current item to the machine

//     // count items across all stages
//     s_inProgress = 0;
//     for (auto* s : stages)
//         s_inProgress += (int)s->get_size();//recounts the products in progress

//     push_log("tick completed", COL_DIM); //adds a dim-colored entry saying the tick happened
// }

// // ── Top bar ───────────────────────────────────────────────────────
// static void draw_topbar(const std::vector<AtomicStage<int,int>*>& stages) { //draws the top bar, name , tick, speed, buttons
//     ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f,0.13f,0.17f,1.f)); //sets the color for next child window
//      // applies the color until the PopStyleColor() is called

//     ImGui::BeginChild("topbar", ImVec2(0, 48), false);// starts the topbar in the ChildWindow

//     ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8);
//     ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 10);

//     ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.10f,0.74f,0.61f,1.f));//color for the "LongDays Factory"
//     ImGui::Text("Long Days Factory");
//     ImGui::PopStyleColor();

//     ImGui::SameLine(0, 16);

//     if (!s_running) {
//         if (ImGui::SmallButton("  Start  ")) {
//             s_running = true;
//             push_log("simulation started", COL_GREEN);
//         }
//     } 
//     else {
//         if (ImGui::SmallButton("  Pause  ")) {
//             s_running = false;
//             push_log("simulation paused", COL_AMBER);
//         }
//     }
//     ImGui::SameLine(0, 6); //tells the ImGui to place the next widget next to the previous one
//     if (ImGui::SmallButton("  Tick  ")) {
//         do_tick(stages);
//     }
//     ImGui::SameLine(0, 6);
//     if (ImGui::SmallButton("  Reset  ")) {
//         s_tick = 0; s_running = false; s_timer = 0;
//         s_finished = 0; s_inProgress = 0; s_selectedIdx = -1;
//         s_log.clear();
//         push_log("reset", COL_AMBER);
//     }//all the ui vlaues are resetted back to the intital stage

//     ImGui::SameLine(0, 20);
//     ImGui::Text("speed");
//     ImGui::SameLine(0, 6);
//     ImGui::SetNextItemWidth(100);
//     ImGui::SliderFloat("##spd", &s_speed, 0.2f, 5.0f, "%.1fx"); // a sliderbar is drawn with width 100px

//     // tick counter on the right
//     ImGui::SameLine(ImGui::GetContentRegionAvail().x - 100); // regulates the space size for the "tick"
//     ImGui::TextColored(COL_DIM, "tick ");
//     ImGui::SameLine(0,2);
//     ImGui::TextColored(ImVec4(0.10f,0.74f,0.61f,1.f), "%03d", s_tick); // 000 -> 001, 002, 003

//     ImGui::EndChild(); //Child window is ended and the topbar is made
//     ImGui::PopStyleColor();
// }

// // ── Stats row ─────────────────────────────────────────────────────
// static void draw_stats() {
//     float w = ImGui::GetContentRegionAvail().x / 4.f - 2.f;//calculates the width of each stat card (Finished, InProgress, etc)

//     //this is a lambda function, it allows to use one function for all 4 stat cards instead of writing 4 functions
//     auto stat_card = [&](const char* label, int val, ImVec4 col) {
//         ImGui::BeginGroup();
//         ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f,0.13f,0.17f,1.f));//starting a child window for the stat card
//         ImGui::BeginChild(label, ImVec2(w, 54), false);
//         ImGui::SetCursorPosY(6); ImGui::SetCursorPosX(8);
//         ImGui::TextColored(COL_DIM, "%s", label);//the stat card name
//         ImGui::SetCursorPosX(8);
//         ImGui::TextColored(col, "%d", val);
//         ImGui::EndChild();
//         ImGui::PopStyleColor();
//         ImGui::EndGroup();
//         ImGui::SameLine(0, 2);
//     };

//     //we are creating the stat cards passing the card's info to the stat_card lambda function
//     stat_card("FINISHED",    s_finished,   COL_GREEN);
//     stat_card("IN PROGRESS", s_inProgress, COL_BLUE);
//     stat_card("BREAKDOWNS",  0,            COL_AMBER);
//     stat_card("LOST",        0,            COL_RED);
//     ImGui::NewLine();
// }

// // ── Machine cards ─────────────────────────────────────────────────
// static void draw_machines(
//     const std::vector<StageBase*>& base, // for names
//     const std::vector<AtomicStage<int,int>*>& atomic) // to fill the data of the machines
// {
//     ImGui::TextColored(COL_DIM, "MACHINES"); // adds the "Machines" text to the top after the stat cards
    

//       // this loop loops through all stages and outputs the data of the machines
//     for (int i = 0; i < (int)atomic.size(); i++) {
//         // only show machines (not conveyors) — skip conveyors by name
//         const char* name = base[i]->get_name();
//         if (std::string(name).find("conveyor") != std::string::npos) continue; 

//         float fill     = atomic[i]->get_fill();
//         bool  selected = (s_selectedIdx == i);
//         bool  working  = fill > 0.f;

//         ImGui::PushID(i); // uses a stack to store ids, each machine information details is given an ID scope, 
//                          //so that they will not conflict with each other

//         // card background highlight if selected
//         if (selected)
//             ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.13f,0.16f,0.22f,1.f));// selected cards get a slightly lighter background
//         else
//             ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f,0.13f,0.17f,1.f));

//         ImGui::BeginChild("mc", ImVec2(0, 70), false);

       
//         ImGui::SetCursorPos(ImVec2(10, 8));

//         // name + state pill on same line
//         ImGui::Text("%s", name);
//         ImGui::SameLine(0, 10);
//         if (working)
//             ImGui::TextColored(COL_GREEN, "[WORKING]");
//         else
//             ImGui::TextColored(COL_DIM,   "[NOT WORKING/EMPTY]");

//         // queue fill bar
//         ImGui::SetCursorPosX(10);
//         ImGui::TextColored(COL_DIM, "queue");
//         ImGui::SameLine(0,6);
//         ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x - 60);
//         ImGui::PushStyleColor(ImGuiCol_PlotHistogram,
//             fill >= 1.f ? COL_RED : COL_GREEN);
//         char lbl[16];
//         snprintf(lbl, sizeof(lbl), "%llu/%llu",
//             atomic[i]->get_size(), atomic[i]->get_capacity());
//         ImGui::ProgressBar(fill, ImVec2(-60, 5), "");
//         ImGui::PopStyleColor();
//         ImGui::SameLine(0,6);
//         ImGui::TextColored(COL_DIM, "%s", lbl);

//         // click to select
//         ImGui::SetCursorPos(ImVec2(0,0));
//         ImGui::InvisibleButton("##sel", ImVec2(-1,-1)); // when the machine is clicked, it will slightly change the color
//         if (ImGui::IsItemClicked()) s_selectedIdx = i; 

//         ImGui::EndChild();
//         ImGui::PopStyleColor();
//         ImGui::Spacing();
//         ImGui::PopID();
//     }
// }

// // ── Conveyor rows ─────────────────────────────────────────────────
// static void draw_conveyors(
//     const std::vector<StageBase*>& base,
//     const std::vector<AtomicStage<int,int>*>& atomic)
// {
//     ImGui::TextColored(COL_DIM, "CONVEYORS");
//     ImGui::Spacing();

//     for (int i = 0; i < (int)atomic.size(); i++) {
//         const char* name = base[i]->get_name();
//         if (std::string(name).find("conveyor") == std::string::npos) continue;

//         ImGui::PushID(100 + i);
//         float fill = atomic[i]->get_fill();

//         ImGui::Text("%-12s", name);
//         ImGui::SameLine(0, 8);
//         ImGui::SetNextItemWidth(-60);
//         ImGui::PushStyleColor(ImGuiCol_PlotHistogram, COL_BLUE);
//         ImGui::ProgressBar(fill, ImVec2(-60, 7), "");
//         ImGui::PopStyleColor();
//         ImGui::SameLine(0,6);
//         ImGui::TextColored(COL_DIM, "%llu/%llu",
//             atomic[i]->get_size(), atomic[i]->get_capacity());

//         ImGui::Spacing();
//         ImGui::PopID();
//     }
// }

// // ── Inspector ─────────────────────────────────────────────────────
// static void draw_inspector(
//     const std::vector<StageBase*>& base,
//     const std::vector<AtomicStage<int,int>*>& atomic)
// {
//     ImGui::TextColored(COL_DIM, "INSPECTOR");
//     ImGui::Spacing();

//     if (s_selectedIdx < 0 || s_selectedIdx >= (int)atomic.size()) {
//         ImGui::TextColored(COL_DIM, "click a machine\nto inspect");
//         return;
//     }

//     int i = s_selectedIdx;
//     auto* a = atomic[i];

//     ImGui::TextColored(ImVec4(0.10f,0.74f,0.61f,1.f), "%s", base[i]->get_name());
//     ImGui::Separator();
//     ImGui::Spacing();

//     auto row = [&](const char* k, const char* v) {
//         ImGui::TextColored(COL_DIM, "%s", k);
//         ImGui::SameLine(110);
//         ImGui::Text("%s", v);
//     };

//     char buf[32];
//     snprintf(buf, sizeof(buf), "%llu", a->get_size());   row("queue size",  buf);
//     snprintf(buf, sizeof(buf), "%llu", a->get_capacity());row("capacity",   buf);
//     snprintf(buf, sizeof(buf), "%.0f%%", a->get_fill()*100.f); row("fill", buf);

//     ImGui::Spacing();
//     ImGui::TextColored(COL_DIM, "state");
//     ImGui::SameLine(110);
//     if (a->get_fill() >= 1.f)
//         ImGui::TextColored(COL_RED,   "FULL");
//     else if (a->get_fill() > 0.f)
//         ImGui::TextColored(COL_GREEN, "WORKING");
//     else
//         ImGui::TextColored(COL_DIM,   "IDLE");

//     ImGui::Spacing();
//     ImGui::Separator();

//     // Queue fill bar
//     ImGui::Spacing();
//     ImGui::TextColored(COL_DIM, "queue fill");
//     float fill = a->get_fill();
//     ImGui::PushStyleColor(ImGuiCol_PlotHistogram,
//         fill >= 1.f ? COL_RED : COL_GREEN);
//     ImGui::ProgressBar(fill, ImVec2(-1, 6), "");
//     ImGui::PopStyleColor();
// }

// // ── Event log ─────────────────────────────────────────────────────
// static void draw_log() {
//     ImGui::TextColored(COL_DIM, "EVENT LOG");
//     ImGui::SameLine(ImGui::GetContentRegionAvail().x - 40);
//     if (ImGui::SmallButton("clear")) s_log.clear();

//     ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.08f,0.09f,0.11f,1.f));
//     ImGui::BeginChild("log", ImVec2(0, 0), false);
//     for (auto& e : s_log) {
//         ImGui::TextColored(COL_DIM, "[%03d]", e.tick);
//         ImGui::SameLine();
//         ImGui::TextColored(e.color, "%s", e.msg.c_str());
//     }
//     ImGui::EndChild();
//     ImGui::PopStyleColor();
// }

// // ── Main render ───────────────────────────────────────────────────
// void render(
//     const std::vector<StageBase*>& baseStages,
//     const std::vector<AtomicStage<int,int>*>& atomicStages)
// {
//     // auto-tick
//     if (s_running) {
//         s_timer += ImGui::GetIO().DeltaTime;
//         if (s_timer >= 1.0f / s_speed) {
//             do_tick(atomicStages);
//             s_timer = 0.f;
//         }
//     }

//     // full-screen window with no chrome
//     ImGuiIO& io = ImGui::GetIO();
//     ImGui::SetNextWindowPos(ImVec2(0,0));
//     ImGui::SetNextWindowSize(io.DisplaySize);
//     ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
//     ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
//     ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f,0.11f,0.14f,1.f));
//     ImGui::Begin("##root", nullptr,
//         ImGuiWindowFlags_NoDecoration |
//         ImGuiWindowFlags_NoMove |
//         ImGuiWindowFlags_NoBringToFrontOnFocus);
//     ImGui::PopStyleVar(2);
//     ImGui::PopStyleColor();

//     draw_topbar(atomicStages);
//     ImGui::Spacing();

//     // stats row
//     ImGui::SetCursorPosX(8);
//     draw_stats();
//     ImGui::Spacing();

//     // main body: left column (machines+conveyors) | right column (inspector)
//     float rightW  = 220.f;
//     float leftW   = ImGui::GetContentRegionAvail().x - rightW - 10.f;
//     float bodyH   = ImGui::GetContentRegionAvail().y - 130.f; // leave room for log

//     // LEFT
//     ImGui::SetCursorPosX(8);
//     ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.09f,0.11f,0.14f,1.f));
//     ImGui::BeginChild("left", ImVec2(leftW, bodyH), false);
//     draw_machines(baseStages, atomicStages);
//     ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
//     draw_conveyors(baseStages, atomicStages);
//     ImGui::EndChild();
//     ImGui::PopStyleColor();

//     ImGui::SameLine(0, 8);

//     // RIGHT — inspector
//     ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f,0.13f,0.17f,1.f));
//     ImGui::BeginChild("right", ImVec2(rightW, bodyH), false);
//     ImGui::SetCursorPos(ImVec2(10,10));
//     draw_inspector(baseStages, atomicStages);
//     ImGui::EndChild();
//     ImGui::PopStyleColor();

//     // LOG at the bottom
//     ImGui::SetCursorPosX(8);
//     ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.11f,0.13f,0.17f,1.f));
//     ImGui::BeginChild("logarea", ImVec2(0, 0), false);
//     ImGui::SetCursorPos(ImVec2(10,8));
//     draw_log();
//     ImGui::EndChild();
//     ImGui::PopStyleColor();

//     ImGui::End();
// }

// } // namespace UI
// } // namespace LongDay

