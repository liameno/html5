#ifndef HTML5_HTML_TIME_ELEMENT_H
#define HTML5_HTML_TIME_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_time_element : html_element {
        html_time_element();

        std::string date_time;
    };
}

#endif
