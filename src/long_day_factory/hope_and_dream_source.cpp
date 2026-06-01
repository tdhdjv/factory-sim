#include "hope_and_dream_source.h"

namespace LongDay {
	b8 HopeAndDreamsSource::feed() {
		HopeAndDreams hopeAndDreams = {100, 100};
		consumer->consume(hopeAndDreams);
		return true;
	}
}
