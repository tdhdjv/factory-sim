#pragma once

#include "backend/sink.h"
#include "backend/source.h"


namespace LongDay {
    template <class In, class Out>
    class Process : public Sink<In>, public Source<Out> {};
}

