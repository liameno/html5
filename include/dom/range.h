#ifndef HTML5_RANGE_H
#define HTML5_RANGE_H

#include "node.h"

namespace html5 {
    struct range {
        enum class compare_boundary_points_c : short {
            start_to_start,
            start_to_end,
            end_to_end,
            end_to_start,
        };

        range();

        node common_ancestor_container;
        void set_start(node node, unsigned long offset);
        void set_end(node node, unsigned long offset);
        void set_start_before(node node);
        void set_start_after(node node);
        void set_end_before(node node);
        void set_end_after(node node);
        void collapse(bool to_start = false);
        void select_node(node node);
        void select_node_contents(node node);

        short compare_boundary_points(unsigned short how, Range sourceRange);
        void deleteContents();

        document_fragment extract_contents();
        document_fragment clone_contents();

        void insert_node(node node);
        void surround_contents(node newParent);

        range clone_range();
        void detach();

        bool is_point_in_range(node node, unsigned long offset);
        short compare_point(node node, unsigned long offset);
        bool intersectsnode(node node);
    };
}

#endif
