#ifndef HTML5_NON_DOCUMENT_TYPE_CHILD_NODE_H
#define HTML5_NON_DOCUMENT_TYPE_CHILD_NODE_H

#include "element.h"

namespace html5 {
    struct non_document_type_child_node {
        element previous_element_sibling;
        element next_element_sibling;
    };
}


#endif
