#ifndef HTML5_XPATH_EVALUATOR_BASE_H
#define HTML5_XPATH_EVALUATOR_BASE_H

#include <string>
#include "node.h"
#include "xpath_result.h"
#include "xpath_expression.h"

namespace html5 {
    struct xpath_ns_resolver {
        std::string lookup_namespace_uri(std::string prefix);
    };

    struct xpath_evaluator_base {

        xpath_expression create_expression(std::string expression, xpath_ns_resolver resolver = {});
        xpath_ns_resolver create_ns_resolver(node node_resolver);
        xpath_result evaluate(std::string expression, node context_node, xpath_ns_resolver resolver = {},
                              unsigned short type = 0, xpath_result result = {});
    };
}

#endif
