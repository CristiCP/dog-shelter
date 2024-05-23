#pragma once
#include <exception>
#include <string>

class Exception : public std::exception {
private:
	std::string error;
public:
	Exception(const std::string& error);
	std::string what();
};