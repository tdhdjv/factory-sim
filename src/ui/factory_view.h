#pragma once
#include "backend/stage.h"
#include <vector>

namespace LongDay {
   namespace PipelineView {
      void draw(
         const std::vector<StageBase*>& baseStages,
         const std::vector<AtomicStage<int,int>*>& atomicStages
         );
   }
}