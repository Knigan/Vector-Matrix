#pragma once
#include <iostream>
#include <string>

class OutOfRangeException: public std::exception {
private:
	std::string error;
public:
	OutOfRangeException () noexcept;
	virtual const char* what() const noexcept; 
};

class IncompatibleDimException: public std::exception { 
private: 
	std::string error;
public:
	IncompatibleDimException(const std::string &a) noexcept;
	
	virtual const char* what() const noexcept;
};