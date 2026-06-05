#pragma once
#include "backend/machine.h"
#include "hope_and_dreams.h"
#include "gloom_and_doom.h"

namespace LongDay {
	class HopeAndDreamsCrusher: public Machine<HopeAndDreams, GloomAndDoom> {
	public:
		explicit HopeAndDreamsCrusher(f32 breakDownProbability);
		const char* get_name() const override; 
		GloomAndDoom transform(const HopeAndDreams& hopeAndDreams) override;
	};
}

