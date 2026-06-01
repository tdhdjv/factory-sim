#include "hope_and_dream_crusher.h"

namespace LongDay {
	HopeAndDreamsCrusher::HopeAndDreamsCrusher(): Machine<HopeAndDreams, GloomAndDoom>(10, 2, 0.01f) {}

	const char* HopeAndDreamsCrusher::get_name() const {
		return "Hope and Dreams Crusher";
	}
	
	GloomAndDoom HopeAndDreamsCrusher::transform(const HopeAndDreams& hopeAndDreams) {
		GloomAndDoom result;
		result.gloom = hopeAndDreams.hopefulness * 2;
		result.doom = hopeAndDreams.aspiration * hopeAndDreams.hopefulness / 2 + 100;
		return result;
	}
}
