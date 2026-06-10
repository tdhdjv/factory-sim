#pragma once
#include "ui_view.h"
#include "ui_state.h"
#include <imgui.h>

namespace LongDay {
	template <typename In, typename Out>
	class TopBar: public UIView {
	private:
		UIState<In,Out>& state;
	public:
		TopBar(UIState<In,Out>& state)
			:state(state) {};
		void draw() override {
			if(ImGui::Button("Start")){
			 state.paused = false;
			};
			ImGui::SameLine();
			if(ImGui::Button("Pause")){
			 state.paused = true;
			};

			ImGui::SameLine();
			//ImGui::SameLine(120.f, 0.f);

			const char* items[] = {"Normal flow", "Random Breakdowns"};
			static int current_item = 0;

			ImGui::SetNextItemWidth(170.f);
			if(ImGui::Combo("Scenarios", &current_item, items, IM_ARRAYSIZE(items))){
				state.currentScene = &state.sceneOptions[current_item];
			};
			ImGui::SameLine();
			//ImGui::SameLine(160.0f, 0.0f);

			std::string ticksCounter = "Ticks " + std::to_string(state.tickCount);

			if (ImGui::Button(ticksCounter.c_str()) || !state.paused){
				state.currentScene->tick();
				state.tickCount++;
			}
		}
	};
}
