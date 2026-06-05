#pragma once
#include "define.h"

namespace LongDay {
    class MachineBase {
    protected:
        u32 progress;
        u64 outputCount;
        b8 broken;
        u32 ticksForProduction;
        f32 failureProbability; 
	public:
		MachineBase(u32 ticksForProduction, f32 failureProbability)
		: progress(0),
		outputCount(0),
		broken(false),
		ticksForProduction(ticksForProduction),
		failureProbability(failureProbability) {};
        virtual ~MachineBase() = default;

        void fix() { broken = false; };
        b8 is_broken() { return broken;};
        u32 get_progress() const { return progress; };
        u32 get_ticks_for_production() const { return ticksForProduction; };
        u64 get_output_count() const { return outputCount; };

        f32 get_failure_probability() const { return failureProbability; }
    };
}
