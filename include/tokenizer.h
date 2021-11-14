#ifndef HTML5_TOKENIZER_H
#define HTML5_TOKENIZER_H

#include <string>
#include <vector>
#include <memory>
#include <stack>

namespace html5 {
    class tokenizer {
    public:
        enum class state {
            data,
            rcdata,
            rawtext,
            script_data,
            plaintext,
            tag_open,
            end_tag_open,
            tag_name,
            rcdata_less_than_sign,
            rcdata_end_tag_open,
            rcdata_end_tag_name,
            rawtext_less_than_sign,
            rawtext_end_tag_open,
            rawtext_end_tag_name,
            script_data_less_than_sign,
            script_data_end_tag_open,
            script_data_end_tag_name,
            script_data_escape_start,
            script_data_escape_start_dash,
            script_data_escaped,
            script_data_escaped_dash,
            script_data_escaped_dash_dash,
            script_data_escaped_less_than_sign,
            script_data_escaped_end_tag_open,
            script_data_escaped_end_tag_name,
            script_data_double_escape_start,
            script_data_double_escaped,
            script_data_double_escaped_dash,
            script_data_double_escaped_dash_dash,
            script_data_double_escaped_less_than_sign,
            script_data_double_escape_end,
            before_attribute_name,
            attribute_name,
            after_attribute_name,
            before_attribute_value,
            attribute_value_double_quoted,
            attribute_value_single_quoted,
            attribute_value_unquoted,
            after_attribute_value_quoted,
            self_closing_start_tag,
            bogus_comment,
            markup_declaration_open,
            comment_start,
            comment_start_dash,
            comment,
            comment_less_than_sign,
            comment_less_than_sign_bang,
            comment_less_than_sign_bang_dash,
            comment_less_than_sign_bang_dash_dash,
            comment_end_dash,
            comment_end,
            comment_end_bang,
            doctype,
            before_doctype_name,
            doctype_name,
            after_doctype_name,
            after_doctype_public_keyword,
            before_doctype_public_identifier,
            doctype_public_identifier_double_quoted,
            doctype_public_identifier_single_quoted,
            after_doctype_public_identifier,
            between_doctype_public_and_system_identifiers,
            after_doctype_system_keyword,
            before_doctype_system_identifier,
            doctype_system_identifier_double_quoted,
            doctype_system_identifier_single_quoted,
            after_doctype_system_identifier,
            bogus_doctype,
            cdata_section,
            cdata_section_bracket,
            cdata_section_end,
            character_reference,
            named_character_reference,
            ambiguous_ampersand,
            numeric_character_reference,
            hexadecimal_character_reference_start,
            decimal_character_reference_start,
            hexadecimal_character_reference,
            decimal_character_reference,
            numeric_character_reference_end,
        };
        enum class token_type {
            doctype,
            tag_start,
            tag_end,
            comment,
            character,
        };

        struct doctype_token {
            std::string name;
            std::string public_identifier{"none"};
            std::string system_identifier{"none"};
            bool is_force_quirks_flag{false};
        };
        struct tag_token {
            std::string name;
            bool is_self_closing{false};
            std::vector<std::shared_ptr<attribute>> attributes;
        };
        struct comment_character_token {
            std::string data;
        };

        struct token {
            token_type type;
            std::shared_ptr<doctype_token> doctype;
            std::shared_ptr<tag_token> tag;
            std::shared_ptr<comment_character_token> comment_character;
        };

        typedef std::vector<std::shared_ptr<token>> stack_t;
        typedef token token_t;
    public:
        static void tokenizie(const std::string &html);
    private:
        static std::shared_ptr<token_t> emit_character_token(const char &data);
        static bool is_whitespace(const char &c);
        static char next_char(const std::string &input, unsigned long &position);
        static bool is_next_few(const std::string &input, const std::string &s, const size_t &position);
    };
}

#endif