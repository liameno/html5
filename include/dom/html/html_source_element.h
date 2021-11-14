#ifndef HTML5_HTML_SOURCE_ELEMENT_H
#define HTML5_HTML_SOURCE_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_source_element : html_element {
        html_source_element();

        std::string src;
        std::string type;
        std::string srcset;
        std::string sizes;
        std::string media;
        unsigned long width;
        unsigned long height;
    };
}

#endif
