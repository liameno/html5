#ifndef HTML5_HTML_TITLE_ELEMENT_H
#define HTML5_HTML_TITLE_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_title_element : html_element {
        html_title_element();

        std::string text;
    };
}

#endif
