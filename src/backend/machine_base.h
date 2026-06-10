#pragma once
#include "define.h"
#include <string>

namespace LongDay {
    class MachineBase {
    protected:
        u64 progress;
        u64 outputCount;
        b8 broken;
        u64 ticksForProduction;
        f32 failureProbability; 
	public:
		MachineBase(u64 ticksForProduction, f32 failureProbability)
		: progress(0),
		outputCount(0),
		broken(false),
		ticksForProduction(ticksForProduction),
		failureProbability(failureProbability) {};
        virtual ~MachineBase() = default;

        virtual void fix() = 0;
		virtual void break_machine() = 0;
		virtual u64 get_queue_cap() const = 0;
		virtual u64 get_queue_fill() const = 0;
		virtual std::string get_str() const = 0;
        b8 is_broken() const { return broken;};
        u64 get_progress() const { return progress; };
        u64 get_ticks_for_production() const { return ticksForProduction; };
        u64 get_output_count() const { return outputCount; };

        f32 get_failure_probability() const { return failureProbability; }
    };
}
