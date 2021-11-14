#ifndef HTML5_XML_DOCUMENT_H
#define HTML5_XML_DOCUMENT_H

#include <string>
#include "document.h"

namespace html5 {
    struct xml_document : public document {
        struct element_creation_options {
            std::string is;
        };
    };
}

#endif
