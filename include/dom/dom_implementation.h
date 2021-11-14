#ifndef HTML5_DOM_IMPLEMENTATION_H
#define HTML5_DOM_IMPLEMENTATION_H

namespace html5 {
    struct dom_implementation {
        document_type createDocumentType(std::string qualified_name, std::string public_id, std::string system_id);
        xml_document createDocument(std::string namespace_, std::string qualified_name, document_type doctype = {});
        document createHTMLDocument(optional std::string title);

        bool has_feature();
    };
}

#endif
