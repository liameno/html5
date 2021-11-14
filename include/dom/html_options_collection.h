#ifndef HTML5_HTML_OPTIONS_COLLECTION_H
#define HTML5_HTML_OPTIONS_COLLECTION_H

#include <string>
#include "html/html_element.h"

namespace html5 {
    struct html_options_collection {
        unsigned long length;

        void add(html_option_element element, html_element before = 0);
        void remove(long index);

        long selected_index;
    };
}

#endif
