#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class InvalidFormat : public std::logic_error
{
public:
	InvalidFormat(const std::string &message) : std::logic_error(message) {}
};

#endif // EXCEPTIONS_H