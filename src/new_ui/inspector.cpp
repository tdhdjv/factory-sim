#include "inspector.h"
#include "ui_color.h"
#include <imgui.h>

namespace LongDay {
	Inspector::Inspector()
		:selectedMachine(nullptr) {};
	void Inspector::draw(){
		ImGui::BeginChild("Inspector", {400, 200}, true);

		ImVec4 stateColors;
		if(selectedMachine) {
			if(selectedMachine->is_broken()) { 
				stateColors = Colors::RED;
			}
			else {
				stateColors = Colors::GREEN;
			}

			ImGui::TextColored(stateColors, "Machine: %s", selectedMachine->get_str().c_str());
			ImGui::Separator();

			ImGui::Text("Progress:");
			ImGui::SameLine();
			ImGui::ProgressBar((f32)selectedMachine->get_progress()/(f32)selectedMachine->get_queue_cap(), ImVec2(-1, 20));
			ImGui::Text("Queue: %llu/%llu", selectedMachine->get_queue_fill(), selectedMachine->get_queue_cap());
			ImGui::Text("Output: %llu", selectedMachine->get_output_count());
			ImGui::Text("Process Time: %llu ticks", selectedMachine->get_ticks_for_production());
			ImGui::Spacing();
			if(ImGui::Button("Force Break")) {
				selectedMachine->break_machine();
			}
			ImGui::SameLine();
			if(ImGui::Button("Instant Repair")) {
				selectedMachine->fix();
			}
		}

		ImGui::EndChild();
	};
	void Inspector::select_machine(MachineBase* machine) {
		selectedMachine = machine;
	}
}
