#ifndef SHELL_H
#define SHELL_H

#include "command.h"
#include "builtins.h"
#include "utils.h"
#include <string>
#include <sys/types.h>
#include <cstdlib>
#include <cstring>
#include <array>
#include <glob.h>
#include <termios.h>
#include <ncurses.h>
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAXLINE 80

class Shell
{
public:
    Shell();
    void executeCommand(const Command &cmd);
    bool isBuiltin(const Command &cmd);
    void executeBuiltin(const Command &cmd);
    void executeExternalCommand(const Command &cmd);
    bool isDirectory(const std::string *path);
    Command parseCommand(const std::string &command);
    std::string readCommand();
    void run();
};

#endif
