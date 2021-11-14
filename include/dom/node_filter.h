#ifndef HTML5_NODE_FILTER_H
#define HTML5_NODE_FILTER_H

#include "node.h"

namespace html5 {
    struct node_filter {
        enum class filter {
            filter_accept = 1,
            filter_reject = 2,
            filter_skip = 3,
        };
        enum class show {
            show_all = 0xFFFFFFF,
            show_element = 0x1,
            show_attribute = 0x2,
            show_text = 0x4,
            show_cdata_section = 0x8,
            show_entity_reference = 0x10,
            show_entity = 0x20,
            show_processing_instruction = 0x40,
            show_comment = 0x80,
            show_document = 0x100,
            show_document_type = 0x200,
            show_document_fragment = 0x400,
            show_notation = 0x800,
        };

        unsigned short accept_node(node node);
    };
}


#endif
