#ifndef BUILTINS_H
#define BUILTINS_H

#include "command.h"
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdlib>
#include <stdexcept>

namespace Builtins {
    bool isBuiltin(const std::string& name);
    void execute(const Command& cmd);
}

#endif // BUILTINS_H