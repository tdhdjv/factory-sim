#pragma once
#include "backend/machine_base.h"
#include "backend/scene.h"
#include "backend/stage.h"
#include "ui_view.h"
#include "inspector.h"
#include <imgui.h>

namespace LongDay {
	template<typename In, typename Out>
	class SceneView : UIView{
	public:
		Scene<In,Out>* scene;
	private:
		Inspector inspector;
		ImVec2 size;
	public:
		SceneView(Scene<In,Out>* scene)
			:size(800, 200), scene(scene) {}
	   static void draw_machine(const MachineBase* machine) {
		  ImGui::Button(machine->get_str().c_str(), ImVec2(255, 100));
		  ImGui::Text("Queue: %llu/%llu", machine->get_queue_fill(), machine->get_queue_cap());
		  ImGui::ProgressBar((f32)machine->get_progress()/(f32)machine->get_ticks_for_production(), ImVec2(200, 30));
	   }

	   static void draw_conveyor(const AtomicStageBase* conveyor) {
               ImGui::SameLine();
               ImGui::BeginGroup();
               ImGui::Text("  conveyor\n==[%llu/%llu]==>", conveyor->get_fill(), conveyor->get_capacity());
               ImGui::ProgressBar((f32)conveyor->get_fill()/(f32)conveyor->get_capacity(), ImVec2(100,20));
               ImGui::EndGroup();
               ImGui::SameLine();
	   }

	   void set_size(ImVec2 size) {
			this->size = size;
	   }

		void draw() override {
			ImGui::BeginChild("Factory Pipeline", size, true);
			ImGui::BeginGroup();
			ImGui::Text("Source");
			ImGui::EndGroup();
			ImGui::SameLine();
			ImGui::Text("->");
			ImGui::SameLine();

			FactoryBase* factory = scene->get_factory();
			for(const auto& ptr: factory->get_stages()) {
				StageBase* stage = ptr.get();
				MachineBase* machine = dynamic_cast<MachineBase*>(stage);
				if(machine != nullptr) {
					ImGui::BeginGroup();
					draw_machine(machine);
					ImGui::EndGroup();
					if(ImGui::IsItemClicked()){
						inspector.select_machine(machine);
					}
				}
				else {
					AtomicStageBase* conveyor = dynamic_cast<AtomicStageBase*>(stage);
					if(conveyor)
						draw_conveyor(conveyor);
				}
			}
			ImGui::SameLine();
			ImGui::Text("->");
			ImGui::SameLine();
			ImGui::BeginGroup();
			ImGui::Text("Sink");
			ImGui::EndGroup();
			ImGui::SameLine();

			ImGui::EndChild();

			ImGui::SameLine();
			inspector.draw();
		}
	};
}

