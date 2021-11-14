#ifndef HTML5_HTML_COLLECTION_H
#define HTML5_HTML_COLLECTION_H

#include <string>
#include "element.h"

namespace html5 {
    struct html_collection {
        unsigned long length;

        element item(unsigned long index);
        element named_item(std::string name);
    };
}

#endif
