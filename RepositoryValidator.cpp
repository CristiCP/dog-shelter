#include "RepositoryValidator.h"

void RepositoryValidator::validateFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw Exception("Failed to open file: " + filename);
    }
}