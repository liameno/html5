#ifndef HTML5_HTML_IFRAME_ELEMENT_H
#define HTML5_HTML_IFRAME_ELEMENT_H

#include <string>
#include "html_element.h"
#include "../document.h"
#include "../dom_token_list.h"

namespace html5 {
    struct html_iframe_element : html_element {
        html_iframe_element();

        std::string src;
        std::string srcdoc;
        std::string name;
        dom_token_list sandbox;
        std::string allow;
        bool allow_fullscreen;
        std::string width;
        std::string height;
        std::string referrer_policy;
        std::string loading;
        document content_document;
        window_proxy content_window;
        document get_svg_document();
    };
}

#endif
