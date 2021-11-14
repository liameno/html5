#ifndef HTML5_HTML_LI_ELEMENT_H
#define HTML5_HTML_LI_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_li_element : html_element {
        html_li_element();

        std::string value;
    };
}

#endif
