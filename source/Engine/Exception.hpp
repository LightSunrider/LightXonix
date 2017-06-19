#pragma once

#include <string>

class Exception {
public:
    Exception() {
        Message = "";
    }
    Exception(const char* message) {
        Message = message;
    }

    const char* Message;
};
