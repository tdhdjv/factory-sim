#pragma once
#include "backend/sink.h"
#include "day.h"

namespace LongDay {
	class DaySink: public Sink<Day> {
	public:
		b8 can_consume() override;
		b8 consume(const Day& day) override;
	};
}
