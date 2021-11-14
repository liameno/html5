#ifndef HTML5_HTML_DATA_ELEMENT_H
#define HTML5_HTML_DATA_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_data_element : html_element {
        html_data_element();

        std::string value;
    };
}

#endif
