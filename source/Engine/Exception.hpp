#pragma once

#include <exception>
#include <string>

namespace le {

class Exception : public std::exception {
public:
    Exception() = default;

    explicit Exception(const char *message) noexcept {
        Message = message;
    }

    virtual const char* what() const noexcept {
        return Message.c_str();
    }

    std::string Message;
};
}
