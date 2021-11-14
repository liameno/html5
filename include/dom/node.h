#ifndef HTML5_NODE_H
#define HTML5_NODE_H

#include <string>

#include "element.h"
#include "node_list.h"

namespace html5 {
    struct node {
        struct get_root_node_options {
            bool composed{false};
        };

        enum class type {
            ELEMENT_NODE,
            ATTRIBUTE_NODE,
            TEXT_NODE,
            CDATA_SECTION_NODE,
            ENTITY_REFERENCE_NODE,
            ENTITY_NODE,
            PROCESSING_INSTRUCTION_NODE,
            COMMENT_NODE,
            DOCUMENT_NODE,
            DOCUMENT_TYPE_NODE,
            DOCUMENT_FRAGMENT_NODE,
            NOTATION_NODE,
        };
        enum class position {
            DOCUMENT_POSITION_DISCONNECTED,
            DOCUMENT_POSITION_PRECEDING,
            DOCUMENT_POSITION_FOLLOWING,
            DOCUMENT_POSITION_CONTAINS,
            DOCUMENT_POSITION_CONTAINED_BY,
            DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC,
        };

        type type{type::ELEMENT_NODE};
        std::string name;
        std::string base_uri;

        bool is_connected{false};
        document owner_document;

        node get_root_node(get_root_node_options options = {});

        node parent_node;
        element parent_element;
        bool has_childnodes();
        node_list child_nodes;

        node first_child;
        node last_child;
        node previous_sibling;
        node next_sibling;

        std::string node_value;
        std::string text_content;

        void normalize();
        node clone_node(bool deep = false);

        bool is_equal_node(node other_node);
        bool is_samenode(node other_node);

        unsigned short compare_document_position(node other);
        bool contains(node other);

        std::string lookup_prefix(std::string namespace_);
        std::string lookup_namespace_uri(std::string prefix);

        bool is_default_namespace(std::string namespace_);

        node insert_before(node node_, node child);
        node append_child(node node_);
        node replace_child(node node_, node child);
        node remove_child(node child);
    };
};

#endif
