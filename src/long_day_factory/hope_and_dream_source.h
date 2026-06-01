#pragma once 
#include "hope_and_dreams.h"
#include "backend/source.h"

namespace LongDay {
	class HopeAndDreamsSource : public Source<HopeAndDreams> {
	public:
		b8 feed() override;
	};
}
