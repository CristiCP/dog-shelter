#include "Exception.h"

Exception::Exception(const std::string& error) {
	this->error = error;
}
std::string Exception::what() {
	return this->error;
}
