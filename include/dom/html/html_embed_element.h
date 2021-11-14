#ifndef HTML5_HTML_EMBED_ELEMENT_H
#define HTML5_HTML_EMBED_ELEMENT_H

#include <string>
#include "html_element.h"
#include "../document.h"

namespace html5 {
    struct html_embed_element : html_element {
        html_embed_element();

        std::string src;
        std::string type;
        std::string width;
        std::string height;
        document get_svg_document();
    };
}

#endif
