#ifndef HTML5_element_H
#define HTML5_element_H

#include <string>
#include <vector>

#include "html_collection.h"
#include "shadow_root.h"
#include "element.h"
#include "attr.h"

namespace html5 {
    struct element {
        std::string namespace_uri;
        std::string prefix;
        std::string local_name;
        std::string tag_name;

        std::string id;
        std::string class_name;
        dom_token_list class_list;
        std::string slot;

        bool has_attributes();
        named_node_map attributes;

        std::vector<std::string> get_attribute_names();
        std::string get_attribute(std::string qualified_name);
        std::string get_attribute_ns(std::string namespace_, std::string localName);
        void set_attribute(std::string qualified_name, std::string value);
        void setattributeibute_ns(std::string namespace_, std::string qualifiedName, std::string value);
        void remove_attribute(std::string qualifiedName);
        void remove_attribute_ns(std::string namespace_, std::string localName);
        bool toggle_attribute(std::string qualifiedName, bool force);
        bool has_attribute(std::string qualifiedName);
        bool has_attribute_ns(std::string namespace_, std::string local_name);

        attr get_attribute_node(std::string qualified_name);
        attr get_attribute_node_ns(std::string namespace_, std::string local_name);
        attr set_attribute_node(attr attr);
        attr set_attribute_node_ns(attr attr);
        attr remove_attribute_node(attr attr);

        shadow_root attach_shadow(shadow_root_init init);
        shadow_root shadow_root;

        element closest(std::string selectors);

        bool matches(std::string selectors);
        bool webkit_matches_selector(std::string selectors);

        html_collection get_elements_by_tag_name(std::string qualified_name);
        html_collection get_elements_by_tag_name_ns(std::string namespace_, std::string local_name);
        html_collection get_elements_by_class_name(std::string class_names);

        element insert_adjacent_element(std::string where, element element);
        void insert_adjacent_text(std::string where, std::string data);
    };

    struct shadow_root_init {
        shadow_root_mode mode;
        bool delegates_focus{false};
        slot_assignment_mode slot_assignment{"named"};
    };
}

#endif
