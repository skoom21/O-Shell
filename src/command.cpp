#include "command.h"

Command::Command(const std::string& name, const std::vector<std::string>& args)
    : name_(name), args_(args) {}

std::string Command::getName() const {
    return name_;
}

const std::vector<std::string>& Command::getArgs() const {
    return args_;
}

CommandParser::CommandParser() {}

Command CommandParser::parse(const std::string& command) {
    
    std::vector<std::string> tokens = tokenize(command);

    
    std::string name = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    return Command(name, args);
}

std::vector<std::string> CommandParser::tokenize(const std::string& command) {
    
    std::vector<std::string> tokens;
    std::string token;
    for (char c : command) {
        if (std::isspace(c)) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}