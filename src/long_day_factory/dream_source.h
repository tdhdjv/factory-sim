#pragma once
#include "backend/source.h"
#include "hope_and_dreams.h"

namespace LongDay {
	class HopeAndDreamsSource: public Source<HopeAndDreams> {
	public:
		b8 feed() override;
	};
}
