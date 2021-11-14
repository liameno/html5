#ifndef HTML5_HTML_QUOTE_ELEMENT_H
#define HTML5_HTML_QUOTE_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_quote_element : html_element {
        html_quote_element();

        std::string cite;
    };
}

#endif
