#ifndef HTML5_NON_ELEMENT_PARENT_NODE_H
#define HTML5_NON_ELEMENT_PARENT_NODE_H

#include "element.h"

namespace html5 {
    struct non_element_parent_node {
        element get_element_by_id(std::string element_id);
    };
}

#endif
