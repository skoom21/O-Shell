#include "utils.h"

void Utils::printError(const std::string& message) {
    // Print error message to stderr
    std::cerr << "Error: " << message << std::endl;
}

void Utils::printInfo(const std::string& message) {
    // Print info message to stdout
    std::cout << "Info: " << message << std::endl;
}