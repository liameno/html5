#ifndef HTML5_DOM_TOKEN_LIST_H
#define HTML5_DOM_TOKEN_LIST_H

namespace html5 {
    struct dom_token_list {
        unsigned long length;
        std::string item(unsigned long index);
        bool contains(std::string token);
        void add(std::string... tokens);
        void remove(std::string... tokens);
        bool toggle(std::string token
                , optional bool force
        );
        bool replace(DOMString token
                , DOMString newToken
        );
        bool supports(DOMString token
        );
        std::string value;
        std::vector<std::string>;
    };
}

#endif
