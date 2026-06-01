#pragma once
#include "backend/machine.h"
#include "day.h"
#include "gloom_and_doom.h"

namespace LongDay{
	class GloomInjector: public Machine<GloomAndDoom, Day> {
	public:
		explicit GloomInjector();
		const char* get_name() const override; 
		Day transform(const GloomAndDoom& gloomAndDoom) override;
	};
}
