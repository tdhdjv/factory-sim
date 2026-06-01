#pragma once
#include "backend/sink.h"
#include "day.h"

namespace LongDay {
	class PrintDaySink: public Sink<Day> {
	public:
		b8 can_consume() override;
		b8 consume(const Day& day) override;
	};
}
