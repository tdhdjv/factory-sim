#pragma once
#include "backend/stage.h"
#include <vector>

namespace LongDay {
   namespace PipelineView {
      void draw(const std::vector<StageAbstract*>& stages);
   }
}