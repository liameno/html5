#ifndef HTML5_HTML_ELEMENT_H
#define HTML5_HTML_ELEMENT_H

#include "../element.h"

namespace html5 {
    struct html_unknown_element {

    };

    struct html_element : public element {
        html_element();

        std::string title;
        std::string lang;
        bool translate;
        std::string dir;

        bool hidden;
        void click();

        std::string access_key;
        std::string access_key_label;
        bool draggable;
        bool spellcheck;
        std::string auto_capitalize;

        std::string inner_text;
        std::string outer_text;

        element_internals attach_internals();
    };
}

#endif
