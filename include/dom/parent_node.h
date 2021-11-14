#ifndef HTML5_PARENT_NODE_H
#define HTML5_PARENT_NODE_H

#include "element.h"
#include "node.h"

namespace html5 {
    struct parent_node {
        html_collection children{};
        element first_element_child;
        element last_element_child;
        unsigned long child_element_count{};

        void prepend(node node);
        void append(node node);
        void replace_children(node node);

        element query_selector(std::string selectors);
        node_list query_selector_all(std::string selectors);
    };
}

#endif
