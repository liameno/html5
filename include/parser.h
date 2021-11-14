#ifndef HTML5_PARSER_H
#define HTML5_PARSER_H

namespace html5 {
    class parser {
    public:
        enum class insertion_mode {
            initial,
            before_html,
            before_head,
            in_head,
            in_head_noscript,
            after_head,
            in_body,
            text,
            in_table,
            in_table_text,
            in_caption,
            in_column_group,
            in_table_body,
            in_row,
            in_cell,
            in_select,
            in_select_in_table,
            in_template,
            after_body,
            in_frameset,
            after_frameset,
            after_after_body,
            after_after_frameset,
        };
    public:

    private:
    };
}

#endif