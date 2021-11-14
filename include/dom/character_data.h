#ifndef HTML5_CHARACTER_DATA_H
#define HTML5_CHARACTER_DATA_H

#include "node.h"

namespace html5 {
    struct character_data : node {
        std::string data;
        unsigned long length;

        std::string substring_data(unsigned long offset, unsigned long count);
        void append_data(std::string data);
        void insert_data(unsigned long offset, std::string data);
        void delete_data(unsigned long offset, unsigned long count);
        void replace_data(unsigned long offset, unsigned long count, std::string data);
    };
}

#endif
