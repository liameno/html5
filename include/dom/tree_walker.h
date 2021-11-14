#ifndef HTML5_TREE_WALKER_H
#define HTML5_TREE_WALKER_H

#include "node.h"

namespace html5 {
    struct tree_walker {
        node root;
        unsigned long what_to_show;
        node_filter filter;
        node current_node;

        node parent_node();
        node first_child();
        node last_child();
        node previous_sibling();
        node next_sibling();
        node previous_node();
        node next_node();
    };
}

#endif
