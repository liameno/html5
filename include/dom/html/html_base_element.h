#ifndef HTML5_HTML_BASE_ELEMENT_H
#define HTML5_HTML_BASE_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_base_element : html_element {
        html_base_element();

        std::string href;
        std::string target;
    };
}

#endif
