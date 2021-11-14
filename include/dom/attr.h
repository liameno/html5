#ifndef HTML5_ATTR_H
#define HTML5_ATTR_H

#include <string>
#include "element.h"

namespace html5 {
    struct attr {
         std::string namespace_uri;
         std::string prefix;
         std::string local_name;
         std::string name;
         std::string value;

         element owner_element;
         bool specified;
    };
}

#endif
