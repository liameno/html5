#ifndef HTML5_HTML_SCRIPT_ELEMENT_H
#define HTML5_HTML_SCRIPT_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_script_element : html_element {
        html_script_element();

        std::string src;
        std::string type;
        bool no_module;
        bool async;
        bool defer;
        std::string cross_origin;
        std::string text;
        std::string integrity;
        std::string referrer_policy;

        static bool supports(std::string type);
    };
}

#endif
