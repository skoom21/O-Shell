#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>

class Command {
public:
    Command(const std::string& name, const std::vector<std::string>& args);
    std::string getName() const;
    const std::vector<std::string>& getArgs() const;

private:
    std::string name_;
    std::vector<std::string> args_;
};

class CommandParser {
public:
    CommandParser();
    Command parse(const std::string& command);
    std::vector<std::string> tokenize(const std::string& command);
};

#endif // COMMAND_H