#include <iostream>

#include "include/tokenizer.h"
#include "include/dom/comment.h"

int main() {
    const std::string html = "<html>a321</html><img/>";
    auto t = new html5::tokenizer();
    t->tokenizie(html);
}
