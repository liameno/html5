
#ifndef HTML5_XPATH_RESULT_H
#define HTML5_XPATH_RESULT_H

#include "node.h"

namespace html5 {
    struct xpath_result {
        enum class type {
            ANY_TYPE,
            NUMBER_TYPE,
            STRING_TYPE,
            BOOLEAN_TYPE,
            UNORDERED_NODE_ITERATOR_TYPE,
            ORDERED_NODE_ITERATOR_TYPE,
            UNORDERED_NODE_SNAPSHOT_TYPE,
            ORDERED_NODE_SNAPSHOT_TYPE,
            ANY_UNORDERED_NODE_TYPE,
            FIRST_ORDERED_NODE_TYPE,
        };

        unsigned short result_type;
        double number_value;
        std::string string_value;
        bool boolean_value;
        node single_node_value;
        bool invalid_iterator_state;
        unsigned long snapshot_length;

        node iterate_next();
        node snapshot_item(unsigned long index);
    };
}

#endif
