#ifndef HTML5_SHADOW_ROOT_H
#define HTML5_SHADOW_ROOT_H

#include "document_fragment.h"
#include "element.h"

namespace html5 {
    enum class shadow_root_mode {
        open,
        closed
    };
    enum class slot_assignment_mode {
        manual,
        named
    };

    struct shadow_root : document_fragment {
        shadow_root_mode mode;
        element host;
    };
}

#endif
