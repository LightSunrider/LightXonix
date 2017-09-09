#pragma once

#include <string>

namespace le {

class Exception {
public:
    Exception() {
        Message = "";
    }
    Exception(const char *message) {
        Message = message;
    }

    const char *Message;
};
}
