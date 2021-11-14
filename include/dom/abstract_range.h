#ifndef HTML5_ABSTRACT_RANGE_H
#define HTML5_ABSTRACT_RANGE_H

#include "node.h"

namespace html5 {
    struct abstract_range {
        node start_container;
        unsigned long start_offset{};
        node end_container;
        unsigned long end_offset{};
        bool collapsed{};
    };
}

#endif
