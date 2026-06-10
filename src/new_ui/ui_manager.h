#pragma once
#include "top_bar.h"
#include "scene_view.h"
#include "ui_view.h"
#include "ui_state.h"
#include "log_view.h"
#include <vector>

namespace LongDay {
	template <typename In, typename Out>
	class UIManager: public UIView {
	private:
		UIState<In, Out> state;
		TopBar<In, Out> bar;
		SceneView<In, Out> sceneView;
		LogView logView;
	public:
		UIManager(std::vector<Scene<In, Out>>&& sceneOptions)
		:state(std::move(sceneOptions)), bar(state), sceneView(state.currentScene), logView() {}
		void draw() override {
			ImGuiIO& io = ImGui::GetIO();
			ImGui::SetNextWindowPos({0, 0});
			ImGui::SetNextWindowSize(io.DisplaySize);
			ImGui::Begin("##host", nullptr,
			 ImGuiWindowFlags_NoDecoration      |
			 ImGuiWindowFlags_NoMove            |
			 ImGuiWindowFlags_NoBringToFrontOnFocus
			);

			bar.draw();
			ImGui::Spacing();
			if(sceneView.scene != state.currentScene) 
				sceneView.scene = state.currentScene;
			sceneView.set_size({io.DisplaySize.x - 400, 200});
			sceneView.draw();
			ImGui::Spacing();
			logView.draw();
			ImGui::End();
		}
	};
}
