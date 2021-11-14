#ifndef HTML5_COMMENT_H
#define HTML5_COMMENT_H

#include "character_data.h"

namespace html5 {
    struct comment : character_data {
        comment(std::string data = {});
    };
}

#endif
