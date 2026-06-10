#pragma once
#include "define.h"
#include <vector>
#include "backend/scene.h"
#include "backend/machine_base.h"

namespace LongDay {
	template<typename In, typename Out>
	struct UIState{
		b8 running;
		b8 paused;
		u32 tickCount;
		std::vector<Scene<In, Out>> sceneOptions;
		Scene<In,Out>* currentScene;
		UIState(std::vector<Scene<In, Out>>&& sceneOptions)
			:running(true), paused(false), tickCount(0), sceneOptions(std::move(sceneOptions)) {
				currentScene = &this->sceneOptions[0];
			}
	};
}

