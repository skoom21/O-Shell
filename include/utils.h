#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <unistd.h>

namespace Utils {
    void printError(const std::string& message);
    void printInfo(const std::string& message);
}

#endif // UTILS_H