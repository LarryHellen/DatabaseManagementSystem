#ifndef INVALIDCOLUMNNAMEEXCEPTION_H
#define INVALIDCOLUMNNAMEEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidColumnNameException : public std::runtime_error {
public:
    explicit InvalidColumnNameException(const std::string& msg) : std::runtime_error(msg) {}
};

#endif // INVALIDCOLUMNNAMEEXCEPTION_H
