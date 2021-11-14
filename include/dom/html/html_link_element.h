#ifndef HTML5_HTML_LINK_ELEMENT_H
#define HTML5_HTML_LINK_ELEMENT_H

#include <string>
#include "../dom_token_list.h"
#include "html_element.h"

namespace html5 {
    struct html_link_element : html_element {
        html_link_element();

        std::string href;
        std::string cross_origin;
        std::string rel;
        std::string as;
        dom_token_list rel_list;
        std::string media;
        std::string integrity;
        std::string hreflang;
        std::string type;
        dom_token_list sizes;
        std::string image_srcset;
        std::string image_sizes;
        std::string referrer_policy;
        bool disabled{false};
    };
}

#endif
