#ifndef HTML5_HTML_ANCHOR_ELEMENT_H
#define HTML5_HTML_ANCHOR_ELEMENT_H

#include <string>
#include "html_element.h"
#include "../dom_token_list.h"

namespace html5 {
    struct html_anchor_element : html_element {
        html_anchor_element();
        
        std::string target;
        std::string download;
        std::string ping;
        std::string rel;
        dom_token_list relList;
        std::string hreflang;
        std::string type;
        std::string text;
        std::string referrerPolicy;
    };
}

#endif
