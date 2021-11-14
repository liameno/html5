#ifndef HTML5_HTML_FORM_CONTROLS_COLLECTION_H
#define HTML5_HTML_FORM_CONTROLS_COLLECTION_H

#include <string>
#include "html_collection.h"
#include "node_list.h"

namespace html5 {
    struct html_form_controls_collection : html_collection {
        element named_item(std::string name);
    };

    struct radio_node_list : node_list {
        std::string value;
    };
}

#endif
