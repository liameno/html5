#ifndef HTML5_NODE_ITERATOR_H
#define HTML5_NODE_ITERATOR_H

#include "node.h"

namespace html5 {
    struct node_iterator {
        node root;
        node referenceNode;
        bool pointerBeforeReferenceNode;
        unsigned long whatToShow;
        node_filter filter;

        node next_node();
        node previous_node();
        void detach();
    };
}

#endif
