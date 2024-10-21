// CustomExceptions.h
#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>

class InvalidItemException : public std::runtime_error {
public:
    explicit InvalidItemException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidDealException : public std::runtime_error {
public:
    explicit InvalidDealException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif