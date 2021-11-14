#ifndef HTML5_NAMED_NODE_MAP_H
#define HTML5_NAMED_NODE_MAP_H

#include "attr.h"

namespace html5 {
    class named_node_map {
        unsigned long length;

        attr item(unsigned long index);
        attr get_named_item(std::string qualified_name);
        attr get_named_item_ns(std::string namespace_, std::string local_name);
        attr set_named_item(attr attr);
        attr set_named_item_ns(attr attr);
        attr remove_named_item(std::string qualified_name);
        attr remove_named_item_ns(std::string namespace_, std::string local_name);
    };
}

#endif
