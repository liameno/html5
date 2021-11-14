#ifndef HTML5_TEXT_H
#define HTML5_TEXT_H

#include <string>

namespace html5 {
    struct text {
        text(std::string data = {});
        text split_text(unsigned long offset);

        std::string whole_text;
    };
}


#endif
