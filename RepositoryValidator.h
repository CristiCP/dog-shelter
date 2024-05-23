#pragma once
#include <string.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "Repository.h"

class RepositoryValidator {
public:
	void validateFile(const std::string& filename);
};