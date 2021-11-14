#ifndef HTML5_HTML_OLIST_ELEMENT_H
#define HTML5_HTML_OLIST_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_olist_element : html_element {
        html_olist_element();

        bool reversed;
        long start;
        std::string type;
    };
}

#endif
