#pragma once
#include "define.h"

namespace LongDay {
    // Non-template base so Scene (and SceneView) can interact with machines
    // without knowing their In/Out types.
    class MachineBase {
    protected:
        f32 originalFailureProbability; // set once at construction
        f32 activeFailureProbability;   // what's actually used at runtime
    public:
        virtual ~MachineBase() = default;

        virtual void fix() = 0;
        virtual b8 is_broken() = 0;
        virtual u32 get_progress() const = 0;
        virtual u32 get_ticks_for_production() const = 0;
        virtual u64 get_output_count() const = 0;

        f32 get_failure_probability() const { return originalFailureProbability; }
        f32 get_active_failure_probability() const { return activeFailureProbability; }
        void set_active_failure_probability(f32 p) { activeFailureProbability = p; }
    };
}
