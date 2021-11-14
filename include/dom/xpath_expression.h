#ifndef HTML5_XPATH_EXPRESSION_H
#define HTML5_XPATH_EXPRESSION_H

#include "xpath_result.h"

namespace html5 {
    struct xpath_expression {
        xpath_result evaluate(node context_node, unsigned short type = 0, xpath_result result = {});
    };
}

#endif
