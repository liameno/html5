#ifndef HTML5_LOCATION_H
#define HTML5_LOCATION_H

#include <string>
#include <vector>

namespace html5 {
    struct location {
        std::string href;
        std::string origin;
        std::string protocol;
        std::string host;
        std::string hostname;
        std::string port;
        std::string pathname;
        std::string search;
        std::string hash;

        void assign(std::string url);
        void replace(std::string url);
        void reload();

        std::vector<std::string> ancestorOrigins;
    };
}

#endif
