#ifndef HTML5_CHILD_NODE_H
#define HTML5_CHILD_NODE_H

#include "node.h"

namespace html5 {
    struct child_node {
        void before(node node);
        void after(node node);
        void replace_with(node node);
        void remove();
    };
}

#endif
