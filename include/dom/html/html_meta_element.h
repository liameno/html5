#ifndef HTML5_HTML_META_ELEMENT_H
#define HTML5_HTML_META_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_meta_element : html_element {
        html_meta_element();

        std::string name;
        std::string http_equiv;
        std::string content;
        std::string media;
    };
}

#endif
