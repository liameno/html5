#ifndef HTML5_XSLT_PROCESSOR_H
#define HTML5_XSLT_PROCESSOR_H

#include <string>
#include "document_fragment.h"
#include "document.h"

namespace html5 {
    struct xslt_processor {
        xslt_processor();
        void import_stylesheet(node style);
        document_fragment transform_to_fragment(node source, document output);
        document transform_to_document(node source);
        template<typename T>
        void set_parameter(std::string namespace_uri, std::string localName, T value);
        auto get_parameter(std::string namespace_uri, std::string localName);
        void remove_parameter(std::string namespace_uri, std::string localName);
        void clear_parameters();
        void reset();
    };
}

#endif
