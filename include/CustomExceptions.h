#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>
#include <string>

/**
 * @class InvalidItemException
 * @brief Exception thrown when an invalid item is encountered.
 */
class InvalidItemException : public std::runtime_error {
public:
    /**
     * @brief Constructs an InvalidItemException with the specified error message.
     * 
     * @param message The error message to be displayed when the exception is thrown.
     */
    explicit InvalidItemException(const std::string& message)
        : std::runtime_error(message) {}
};

/**
 * @class InvalidDealException
 * @brief Exception thrown when an invalid deal is encountered.
 */
class InvalidDealException : public std::runtime_error {
public:
    /**
     * @brief Constructs an InvalidDealException with the specified error message.
     * 
     * @param message The error message to be displayed when the exception is thrown.
     */
    explicit InvalidDealException(const std::string& message)
        : std::runtime_error(message) {}
};

#endif // CUSTOM_EXCEPTIONS_H
