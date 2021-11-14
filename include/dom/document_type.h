#ifndef HTML5_DOCUMENT_TYPE_H
#define HTML5_DOCUMENT_TYPE_H

#include <string>

namespace html5 {
    struct document_type {
        std::string name;
        std::string public_id;
        std::string system_id;
    };
}

#endif
