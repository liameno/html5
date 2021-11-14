#ifndef HTML5_STATIC_RANGE_H
#define HTML5_STATIC_RANGE_H

#include "node.h"
#include "abstract_range.h"

namespace html5 {
    struct static_range_init {
        node start_container;
        unsigned long start_offset{};
        node end_container;
        unsigned long end_offset{};
    };

    struct static_range : abstract_range {
        static_range(static_range_init init);
    };
}


#endif
