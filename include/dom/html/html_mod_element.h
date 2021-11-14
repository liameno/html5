#ifndef HTML5_HTML_MOD_ELEMENT_H
#define HTML5_HTML_MOD_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_mod_element : html_element {
        html_mod_element();

        std::string cite;
        std::string dite_time;
    };
}

#endif
