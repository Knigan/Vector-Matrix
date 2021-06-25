#include "Exception.h"

OutOfRangeException::OutOfRangeException() noexcept: error("Non-existent array element was accessed") {}

const char* OutOfRangeException::what() const noexcept {
	return error.c_str();
}

IncompatibleDimException::IncompatibleDimException (const std::string &a) noexcept: error(a) {}

const char* IncompatibleDimException::what () const noexcept {
	return error.c_str();
}