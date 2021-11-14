#ifndef HTML5_HTML_OBJECT_ELEMENT_H
#define HTML5_HTML_OBJECT_ELEMENT_H

#include <string>
#include "html_element.h"

namespace html5 {
    struct html_object_element : html_element {
        html_object_element();

        std::string data;
        std::string type;
        std::string name;
        html_form_element form;
        std::string width;
        std::string height;
        document content_document;
        window_proxy content_window;
        document get_svg_document();

        bool will_validate;
        validity_state validity;
        std::string validation_message;
        bool check_validity();
        bool report_validity();
        void set_custom_validity(std::string error);
    };
}

#endif
