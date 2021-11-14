#include <memory>
#include <iostream>

#include "../include/tokenizer.h"

namespace html5 {
    void tokenizer::tokenizie(const std::string &html) {
        size_t position = 0;

        auto stack = std::make_shared<stack_t>();
        std::shared_ptr<token_t> current_token;
        std::shared_ptr<attribute> current_attribute;
        std::shared_ptr<token_t> last_open_tag_token;
        state current_state = state::data;
        state return_state = state::data;
        std::string temporary_buffer;
        int character_reference_code = 0;
        bool is_appropriate_end_tag_token = false;
        bool is_else = false;
        bool is_reconsume = false;
        char current_char = '\0';
        bool is_work = true;

        while (position < html.size()) {
            switch (current_state) {
                case state::data:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0026') {
                        return_state = state::data;
                        current_state = state::character_reference;
                    } else if (current_char == '\u003C') {
                        current_state = state::tag_open;
                    } else if (current_char == '\u0000') {

                    } else {
                        current_token = emit_character_token(current_char);
                        stack->push_back(current_token);
                    }
                    break;
                case state::rcdata:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0026') {
                        return_state = state::rcdata;
                        current_state = state::character_reference;
                    } else if (current_char == '\u003C') {
                        current_state = state::comment_less_than_sign;
                    }
                    break;
                case state::rawtext:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003C') {
                        current_state = state::rawtext_less_than_sign;
                    }
                    break;
                case state::script_data:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003C') {
                        current_state = state::script_data_less_than_sign;
                    }
                    break;
                case state::plaintext:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0000') {

                    } else {
                        current_token = emit_character_token(current_char);
                        stack->push_back(current_token);
                    }

                    break;
                case state::tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0021') {
                        current_state = state::markup_declaration_open;
                    } else if (current_char == '\u002F') {
                        current_state = state::end_tag_open;
                    } else if (std::isalpha(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::tag_start;
                        current_token->tag = std::make_shared<tag_token>();
                        stack->push_back(current_token);
                        current_state = state::tag_name;
                        last_open_tag_token = current_token;
                        is_reconsume = true;
                    } else if (current_char == '\u003F') {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::comment;
                        current_token->comment_character = std::make_shared<comment_character_token>();
                        stack->push_back(current_token);
                        current_state = state::bogus_comment;
                        is_reconsume = true;
                    } else {
                        current_token = emit_character_token(current_char);
                        stack->push_back(current_token);
                        current_state = state::data;
                        is_reconsume = true;
                    }
                    break;
                case state::end_tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (std::isalpha(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::tag_end;
                        current_token->tag = std::make_shared<tag_token>();
                        stack->push_back(current_token);
                        current_state = state::tag_name;
                        is_reconsume = true;
                    } else if (current_char == '\u003E') {
                        current_state = state::tag_name;
                    } else {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::comment;
                        current_token->comment_character = std::make_shared<comment_character_token>();
                        stack->push_back(current_token);
                        current_state = state::bogus_comment;
                        is_reconsume = true;
                    }
                    break;
                case state::tag_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        current_state = state::before_attribute_name;
                    } else if (current_char == '\u002F') {
                        current_state = state::self_closing_start_tag;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token->tag->name += std::tolower(current_char);
                    } else if (current_char == '\u0000') {

                    } else {
                        current_token->tag->name += current_char;
                    }
                    break;
                case state::rcdata_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002F') {
                        temporary_buffer.clear();
                        current_state = state::rcdata_end_tag_open;
                    } else {
                        current_token = emit_character_token('\u003C');
                        stack->push_back(current_token);
                        current_state = state::rcdata;
                        is_reconsume = true;
                    }
                    break;
                case state::rcdata_end_tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (std::isalpha(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::tag_end;
                        current_token->tag = std::make_shared<tag_token>();
                        stack->push_back(current_token);
                        current_state = state::rcdata_end_tag_name;
                        is_reconsume = true;
                    } else {
                        current_token = emit_character_token('\u003C');
                        stack->push_back(current_token);
                        current_token = emit_character_token('\u002F');
                        stack->push_back(current_token);
                        current_state = state::rcdata;
                        is_reconsume = true;
                    }
                    break;
                case state::rcdata_end_tag_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    is_appropriate_end_tag_token = (last_open_tag_token->tag->name == current_token->tag->name);
                    is_else = false;

                    if (is_whitespace(current_char) && is_appropriate_end_tag_token) {
                        current_state = state::before_attribute_name;
                        is_else = true;
                    } else if (current_char == '\u002F' && is_appropriate_end_tag_token) {
                        current_state = state::self_closing_start_tag;
                        is_else = true;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token->tag->name += std::tolower(current_char);
                        temporary_buffer += current_char;
                    } else if (std::isalpha(current_char) && std::islower(current_char)) {
                        current_token->tag->name += current_char;
                        temporary_buffer += current_char;
                    } else {
                        is_else = true;
                    }

                    if (is_else) {
                        current_state = state::rcdata;
                        is_reconsume = true;
                    }
                    break;
                case state::rawtext_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002F') {
                        temporary_buffer.clear();
                        current_state = state::rawtext_end_tag_open;
                    } else {
                        current_state = state::rawtext;
                        is_reconsume = true;
                    }
                    break;
                case state::rawtext_end_tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (std::isalpha(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::tag_end;
                        current_token->tag = std::make_shared<tag_token>();
                        current_state = state::rawtext_end_tag_name;
                        stack->push_back(current_token);
                        is_reconsume = true;
                    } else {
                        current_state = state::rawtext;
                        is_reconsume = true;
                    }
                    break;
                case state::rawtext_end_tag_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    is_appropriate_end_tag_token = (last_open_tag_token->tag->name == current_token->tag->name);
                    is_else = false;

                    if (is_whitespace(current_char) && is_appropriate_end_tag_token) {
                        current_state = state::before_attribute_name;
                        is_else = true;
                    } else if (current_char == '\u002F' && is_appropriate_end_tag_token) {
                        current_state = state::self_closing_start_tag;
                        is_else = true;
                    } else if (current_char == '\u003E' && is_appropriate_end_tag_token) {
                        current_state = state::data;
                        current_token = nullptr;
                        is_else = true;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token->tag->name += std::tolower(current_char);
                        temporary_buffer += current_char;
                    } else if (std::isalpha(current_char) && std::islower(current_char)) {
                        current_token->tag->name += current_char;
                        temporary_buffer += current_char;
                    } else {
                        is_else = true;
                    }

                    if (is_else) {
                        current_state = state::rawtext;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002F') {
                        temporary_buffer.clear();
                        current_state = state::script_data_end_tag_open;
                    } else if (current_char == '\u0021') {
                        current_state = state::script_data_escape_start;
                    } else {
                        current_state = state::script_data;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_end_tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (std::isalpha(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::tag_end;
                        current_token->tag = std::make_shared<tag_token>();
                        stack->push_back(current_token);
                        current_state = state::script_data_end_tag_name;
                        is_reconsume = true;
                    } else {
                        current_state = state::script_data;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_end_tag_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    is_appropriate_end_tag_token = (last_open_tag_token->tag->name == current_token->tag->name);
                    is_else = false;

                    if (is_whitespace(current_char) && is_appropriate_end_tag_token) {
                        current_state = state::before_attribute_name;
                        is_else = true;
                    } else if (current_char == '\u002F' && is_appropriate_end_tag_token) {
                        current_state = state::self_closing_start_tag;
                        is_else = true;
                    } else if (current_char == '\u003E' && is_appropriate_end_tag_token) {
                        current_state = state::data;
                        current_token = nullptr;
                        is_else = true;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token->tag->name += std::tolower(current_char);
                        temporary_buffer += current_char;
                    } else if (std::isalpha(current_char) && std::islower(current_char)) {
                        current_token->tag->name += current_char;
                        temporary_buffer += current_char;
                    } else {
                        is_else = true;
                    }

                    if (is_else) {
                        current_state = state::script_data;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_escape_start:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::script_data_escape_start_dash;
                    } else {
                        current_state = state::script_data;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_escape_start_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::script_data_escaped_dash_dash;
                    } else {
                        current_state = state::script_data;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_escaped:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::script_data_escaped_dash;
                    } else if (current_char == '\u003C') {
                        current_state = state::script_data_escaped_less_than_sign;
                    } else if (current_char == '\u0000') {

                    } else {

                    }
                    break;
                case state::script_data_escaped_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::script_data_escaped_dash_dash;
                    } else if (current_char == '\u003C') {
                        current_state = state::script_data_escaped_less_than_sign;
                    } else if (current_char == '\u0000') {
                        current_state = state::script_data_escaped;
                    } else {
                        current_state = state::script_data_escaped;
                    }
                    break;
                case state::script_data_escaped_dash_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::script_data_escaped_less_than_sign;
                    } else if (current_char == '\u003C') {
                        current_state = state::script_data;
                    } else if (current_char == '\u003E') {
                        current_state = state::script_data_escaped;
                    } else if (current_char == '\u0000') {
                        current_state = state::script_data_escaped;
                    } else {
                        current_state = state::script_data_escaped;
                    }
                    break;
                case state::script_data_escaped_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002F') {
                        temporary_buffer.clear();
                        current_state = state::script_data_escaped_end_tag_open;
                    } else if (std::isalpha(current_char)) {
                        temporary_buffer.clear();
                        current_state = state::script_data_double_escape_start;
                        is_reconsume = true;
                    } else {
                        current_state = state::script_data_escaped;
                        is_reconsume = true;
                    }
                    break;
                case state::script_data_escaped_end_tag_open:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_escaped_end_tag_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escape_start:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escaped:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escaped_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escaped_dash_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escaped_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::script_data_double_escape_end:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::before_attribute_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        //ignore
                    } else if (current_char == '\u002F' || current_char == '\u003E') {
                        current_state = state::after_attribute_name;
                        is_reconsume = true;
                    } else if (current_char == '\u003D') {
                        current_attribute = std::make_shared<attribute>();
                        current_attribute->name = current_char;
                        current_token->tag->attributes.push_back(current_attribute);
                        current_state = state::attribute_name;
                    } else {
                        current_attribute = std::make_shared<attribute>();
                        current_token->tag->attributes.push_back(current_attribute);
                        current_state = state::attribute_name;
                    }
                    break;
                case state::attribute_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    is_else = false;

                    if (is_whitespace(current_char) || current_char == '\u002F' || current_char == '\u003E') {
                        current_state = state::after_attribute_name;
                        is_reconsume = true;
                    } else if (current_char == '\u003D') {
                        current_state = state::before_attribute_value;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_attribute->name += std::tolower(current_char);
                    } else if (current_char == '\u0000') {

                    } else if (current_char == '\u0022' || current_char == '\u0027' || current_char == '\u003C') {
                        is_else = true;
                    } else {
                        is_else = true;
                    }

                    if (is_else) {
                        current_attribute->name += current_char;
                    }

                    break;
                case state::after_attribute_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        //ignore
                    } else if (current_char == '\u002F') {
                        current_state = state::self_closing_start_tag;
                    } else if (current_char == '\u003D') {
                        current_state = state::before_attribute_value;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        current_attribute = std::make_shared<attribute>();
                        current_token->tag->attributes.push_back(current_attribute);
                        is_reconsume = true;
                    }
                    break;
                case state::before_attribute_value:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        //ignore
                    } else if (current_char == '\u0022') {
                        current_state = state::attribute_value_double_quoted;
                    } else if (current_char == '\u0027') {
                        current_state = state::attribute_value_single_quoted;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                    } else {
                        current_state = state::attribute_value_unquoted;
                        is_reconsume = true;
                    }
                    break;
                case state::attribute_value_double_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0022') {
                        current_state = state::after_attribute_value_quoted;
                    } else if (current_char == '\u0026') {
                        return_state = state::attribute_value_double_quoted;
                        current_state = state::character_reference;
                    } else if (current_char == '\u0000') {

                    } else {
                        current_attribute->value += current_char;
                    }
                    break;
                case state::attribute_value_single_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0027') {
                        current_state = state::after_attribute_value_quoted;
                    } else if (current_char == '\u0026') {
                        return_state = state::attribute_value_single_quoted;
                        current_state = state::character_reference;
                    } else if (current_char == '\u0000') {

                    } else {
                        current_attribute->value += current_char;
                    }
                    break;
                case state::attribute_value_unquoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    is_else = false;

                    if (is_whitespace(current_char)) {
                        current_state = state::before_attribute_name;
                    } else if (current_char == '\u0026') {
                        return_state = state::attribute_value_unquoted;
                        current_state = state::character_reference;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                    } else if (current_char == '\u0022' || current_char == '\u0027' || current_char == '\u003C' ||
                               current_char == '\u003D' || current_char == '\u0060') {
                        is_else = true;
                    }

                    if (is_else) {
                        current_attribute->value += current_char;
                    }
                    break;
                case state::after_attribute_value_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        current_state = state::before_attribute_name;
                    } else if (current_char == '\u002F') {
                        current_state = state::self_closing_start_tag;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                    } else {
                        current_state = state::attribute_name;
                        is_reconsume = true;
                    }
                    break;
                case state::self_closing_start_tag:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003E') {
                        current_token->tag->is_self_closing = true;
                        current_state = state::data;
                    } else {
                        current_state = state::before_attribute_name;
                        is_reconsume = true;
                    }
                    break;
                case state::bogus_comment:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003E') {
                        current_state = state::data;
                    } else if (current_char == '\u0000') {

                    } else {
                        current_token->comment_character->data += current_char;
                    }
                    break;
                case state::markup_declaration_open:
                    if (is_next_few(html, "--", position)) {
                        position += 2;
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::comment;
                        current_token->comment_character = std::make_shared<comment_character_token>();
                        stack->push_back(current_token);
                        current_state = state::comment_start;
                    } else if (is_next_few(html, "DOCTYPE", position)) {
                        position += 7;
                        current_state = state::doctype;
                    } else if (is_next_few(html, "[CDATA[", position)) {
                        position += 7;
                    } else {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::comment;
                        current_token->comment_character = std::make_shared<comment_character_token>();
                        stack->push_back(current_token);
                        current_state = state::bogus_comment;
                    }
                    break;
                case state::comment_start:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::comment_start_dash;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_start_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::comment_end;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        current_token->comment_character->data += '\u002D';
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003C') {
                        current_token->comment_character->data += current_char;
                        current_state = state::comment_less_than_sign;
                    } else if (current_char == '\u002D') {
                        current_state = state::comment_end_dash;
                    } else if (current_char == '\u0000') {

                    } else {
                        current_token->comment_character->data += current_char;
                    }
                    break;
                case state::comment_less_than_sign:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u0021') {
                        current_token->comment_character->data += current_char;
                        current_state = state::comment_less_than_sign_bang;
                    } else if (current_char == '\u003C') {
                        current_token->comment_character->data += current_char;
                    } else {
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_less_than_sign_bang:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::comment_less_than_sign_bang_dash;
                    } else {
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_less_than_sign_bang_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::comment_less_than_sign_bang_dash_dash;
                    } else {
                        current_state = state::comment_end_dash;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_less_than_sign_bang_dash_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003E') {
                        current_state = state::comment_end;
                        is_reconsume = true;
                    } else {
                        current_state = state::comment_end;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_end_dash:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_state = state::comment_end;
                    } else {
                        current_token->comment_character->data += '\u002D';
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_end:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else if (current_char == '\u0021') {
                        current_state = state::comment_end_bang;
                    } else if (current_char == '\u002D') {
                        current_token->comment_character->data += '\u002D';
                    } else {
                        current_token->comment_character->data += '\u002D';
                        current_token->comment_character->data += '\u002D';
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::comment_end_bang:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (current_char == '\u002D') {
                        current_token->comment_character->data += '\u002D';
                        current_token->comment_character->data += '\u002D';
                        current_token->comment_character->data += '\u0021';
                        current_state = state::comment_end_dash;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        current_token->comment_character->data += '\u002D';
                        current_token->comment_character->data += '\u002D';
                        current_token->comment_character->data += '\u0021';
                        current_state = state::comment;
                        is_reconsume = true;
                    }
                    break;
                case state::doctype:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        current_state = state::before_doctype_name;
                    } else if (current_char == '\u003E') {
                        current_state = state::before_doctype_name;
                        is_reconsume = true;
                    } else {
                        current_state = state::before_doctype_name;
                        is_reconsume = true;
                    }
                    break;
                case state::before_doctype_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        //ignore
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::doctype;
                        current_token->doctype->name = std::tolower(current_char);
                        stack->push_back(current_token);
                        current_state = state::doctype_name;
                    } else if (current_char == '\u003E') {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::doctype;
                        current_token->doctype->is_force_quirks_flag = true;
                        stack->push_back(current_token);
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        current_token = std::make_shared<token_t>();
                        current_token->type = token_type::doctype;
                        current_token->doctype->name = current_char;
                        stack->push_back(current_token);
                        current_state = state::doctype_name;
                    }
                    break;
                case state::doctype_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        current_state = state::after_doctype_name;
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else if (std::isalpha(current_char) && std::isupper(current_char)) {
                        current_token->comment_character->data += std::tolower(current_char);
                    } else if (current_char == '\u0000') {

                    } else {
                        current_token->comment_character->data += current_char;
                    }
                    break;
                case state::after_doctype_name:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    if (is_whitespace(current_char)) {
                        //ignore
                    } else if (current_char == '\u003E') {
                        current_state = state::data;
                        current_token = nullptr;
                    } else {
                        if (is_next_few(html, "PUBLIC", position)) {
                            position += 6;
                            current_state = state::after_doctype_public_keyword;
                        } else if (is_next_few(html, "SYSTEM", position)) {
                            position += 6;
                            current_state = state::after_doctype_system_keyword;
                        } else {
                            current_token->doctype->is_force_quirks_flag = true;
                            current_state = state::bogus_doctype;
                            is_reconsume = true;
                        }
                    }
                    break;
                case state::after_doctype_public_keyword:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::before_doctype_public_identifier:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::doctype_public_identifier_double_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::doctype_public_identifier_single_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::after_doctype_public_identifier:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::between_doctype_public_and_system_identifiers:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::after_doctype_system_keyword:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::before_doctype_system_identifier:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::doctype_system_identifier_double_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::doctype_system_identifier_single_quoted:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::after_doctype_system_identifier:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::bogus_doctype:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::cdata_section:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::cdata_section_bracket:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::cdata_section_end:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::character_reference:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;
                    temporary_buffer = '\u0026';

                    if (std::isalnum(current_char)) {
                        current_state = state::named_character_reference;
                        is_reconsume = true;
                    } else if (current_char == '\u0023') {
                        temporary_buffer += current_char;
                        current_state = state::numeric_character_reference;
                    } else {
                        current_char = '\0';
                    }
                    break;
                case state::named_character_reference:

                    break;
                case state::ambiguous_ampersand:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::numeric_character_reference:
                    character_reference_code = 0;
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::hexadecimal_character_reference_start:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::decimal_character_reference_start:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::hexadecimal_character_reference:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::decimal_character_reference:
                    !is_reconsume ? current_char = next_char(html, position) : is_reconsume = false;

                    break;
                case state::numeric_character_reference_end:
                    if (character_reference_code == 0x00) {
                        character_reference_code = 0xFFFD;
                    } else if (character_reference_code > 0x10FFFF) {
                        character_reference_code = 0xFFFD;
                    }
                    break;
            }
        }

        for (const auto &item: *stack) {
            std::string type_s;
            std::string value;

            switch (item->type) {
                case token_type::doctype:
                    type_s = "doctype";
                    value = item->doctype->name;
                    break;
                case token_type::tag_start:
                    type_s = "tag_open";
                    value = item->tag->name + " | " + std::to_string(item->tag->is_self_closing);
                    break;
                case token_type::tag_end:
                    type_s = "tag_end";
                    value = item->tag->name + " | " + std::to_string(item->tag->is_self_closing);
                    break;
                case token_type::comment:
                    type_s = "comment";
                    value = item->comment_character->data;
                    break;
                case token_type::character:
                    type_s = "character";
                    value = item->comment_character->data;
                    break;
            }

            std::cout << type_s << " | " << value << std::endl;
        }
    }

    std::shared_ptr<token_t> tokenizer::emit_character_token(const char &data) {
        auto t = std::make_shared<token_t>();
        t->type = token_type::character;
        t->comment_character = std::make_shared<comment_character_token>();
        t->comment_character->data = data;
        return t;
    }

    bool tokenizer::is_whitespace(const char &c) {
        return c == '\u0009' || c == '\u000A' || c == '\u000C' || c == '\u0020';
    }

    char tokenizer::next_char(const std::string &input, unsigned long &position) {
        if (position >= input.length()) {
            return '\0';
        }

        return input[position++];
    }

    bool tokenizer::is_next_few(const std::string &input, const std::string &s, const size_t &position) {
        auto size = s.size();

        for (size_t i = 0; i < size; ++i) {
            auto f = position + i;
            if (next_char(input, f) != s[i]) {
                return false;
            }
        }

        return true;
    }
}