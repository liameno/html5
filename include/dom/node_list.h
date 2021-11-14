#ifndef HTML5_NODE_LIST_H
#define HTML5_NODE_LIST_H

#include <vector>
#include "node.h"

namespace html5 {
    struct node_list {
        node item(unsigned long index);

        unsigned long length;
        std::vector<html5::node> nodes;
    };
}

#endif