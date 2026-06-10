#pragma once
#include "backend/stage.h"
#include <memory>

namespace LongDay {
	class FactoryBase {
	protected:
		std::vector<std::unique_ptr<StageBase>> stages;
	public:
		std::vector<std::unique_ptr<StageBase>>& get_stages() { return stages; }
	};
}
