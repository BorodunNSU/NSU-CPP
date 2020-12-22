#pragma once

#include <exception>

class ListException : public std::exception {
private:
    std::string errorStr;
public:
    ListException() = default;

    explicit ListException(const std::string &errorMessage) {
        errorStr = errorMessage;
    }

    [[nodiscard]] const char *what() const noexcept override {
        return errorStr.c_str();
    }
};