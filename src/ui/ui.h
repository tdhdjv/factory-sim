#pragma once
#include "imgui.h"
#include "backend/stage.h"
#include <vector>

namespace LongDay {
   namespace UI {
      void render (const std::vector<StageAbstract*>& stages);
   }

}