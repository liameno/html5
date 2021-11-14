#ifndef HTML5_DOCUMENT_H
#define HTML5_DOCUMENT_H

#include <string>

#include "node.h"
#include "element.h"
#include "html_collection.h"
#include "attr.h"
#include "dom_implementation.h"
#include "document_type.h"
#include "text.h"
#include "cdata_section.h"
#include "processing_instruction.h"
#include "comment.h"
#include "range.h"
#include "node_iterator.h"
#include "tree_walker.h"
#include "node_filter.h"
#include "xml_document.h"
#include "location.h"
#include "html_script_element.h.h"

namespace html5 {
    struct document : public node {
        enum class ready_state { loading, interactive, complete };
        enum class visibility_state { visible, hidden };

        location location;
        std::string domain;
         std::string referrer;
        std::string cookie;
         std::string lastModified;
         DocumentReadyState readyState;

        element object(std::string name);
        std::string title;
        std::string dir;
        HTMLElement? body;
         HTMLHeadElement? head;
        html_collection images;
        html_collection embeds;
        html_collection plugins;
        html_collection links;
        html_collection forms;
        html_collection scripts;
        node_list get_elements_by_name(std::string elementName);
        html_script_element current_script;

        document open(optional std::string unused1, optional std::string unused2);
        window_proxy? open(std::string url, std::string name, std::string features);
        void close();
        void write(std::string... text);
        void writeln(std::string... text);

         window_proxy? defaultView;
        bool has_focus();
        std::string design_mode;
        bool exec_command(std::string commandId, optional bool showUI = false, optional std::string value = "");
        bool query_command_enabled(std::string commandId);
        bool query_command_indeterm(std::string commandId);
        bool query_command_state(std::string commandId);
        bool query_command_supported(std::string commandId);
        std::string query_command_value(std::string commandId);
         bool hidden;
         visibility_state visibilityState;
    };
};

#endif
