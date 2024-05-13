#include "shell.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

const std::array<const char *, 7> colors = {
    "\033[1;30m", "\033[1;31m", "\033[1;32m", "\033[1;33m",
    "\033[1;34m", "\033[1;35m", "\033[1;36m"};

Shell::Shell()
{

    chdir(getenv("HOME"));
}

void Shell::run()
{
    while (true)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr)
        {
            std::cout << "\n"
                      << "\033[1;29m" << cwd << "\033[0m" << "\n";
        }
        fflush(stdout);

        std::string command = readCommand();

        if (command.empty())
        {
            continue;
        }

        Command cmd = parseCommand(command);

        executeCommand(cmd);
    }
}

bool Shell::isDirectory(const std::string *path)
{
    struct stat pathStat;
    if (stat(path->c_str(), &pathStat) != 0)
    {
        return false;
    }
    return S_ISDIR(pathStat.st_mode);
}

static char **custom_completion(const char *text, int start, int end)
{
    // std:: cout << text << std::endl;
    Shell s1;
    std::vector<std::string> matches;
    char **suggestions = rl_completion_matches(text, &rl_filename_completion_function);
    for (size_t i = 0; suggestions[i]; i++)
    {
        matches.push_back(suggestions[i]);
    }

    free(suggestions);

    std::string input(text);
    if (input == "")
    {
        std::vector<std::string> directories;
        for (const auto &match : matches)
        {
            if (s1.isDirectory(&match))
            {
                directories.push_back(match);
            }
        }
        matches = directories;
    }
    else if (matches.size() > 10)
    {
        std::cout << "\nToo many suggestions. Display all? (y/n): ";
        char choice = getchar();
        if (choice != 'y' && choice != 'Y')
        {
            return nullptr;
        }
        else
        {
            for (const auto &match : matches)
            {
                std::cout << match << std::endl;
            }
        }
    }

    char **result = new char *[matches.size() + 1];
    for (size_t i = 0; i < matches.size(); i++)
    {
        result[i] = new char[matches[i].size() + 1];
        strcpy(result[i], matches[i].c_str());
    }
    result[matches.size()] = nullptr;
    return result;
}

std::string Shell::readCommand()
{
    rl_initialize();

    rl_attempted_completion_function = custom_completion;

    char *input = readline("\033[1;34m osh>\033[0m");

    add_history(input);

    std::string command(input);

    free(input);

    return command;
}

Command Shell::parseCommand(const std::string &command)
{
    CommandParser parser;
    return parser.parse(command);
}

void Shell::executeCommand(const Command &cmd)
{
    if (isBuiltin(cmd))
    {
        executeBuiltin(cmd);
    }
    else
    {
        executeExternalCommand(cmd);
    }
}

bool Shell::isBuiltin(const Command &cmd)
{

    return Builtins::isBuiltin(cmd.getName());
}

void Shell::executeBuiltin(const Command &cmd)
{

    try
    {
        Builtins::execute(cmd);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void Shell::executeExternalCommand(const Command &cmd)
{

    pid_t pid = fork();
    if (pid < 0)
    {
        std::cerr << "Error: Fork failed" << std::endl;
        return;
    }
    if (pid == 0)
    {

        std::vector<char *> args;
        args.push_back(const_cast<char *>(cmd.getName().c_str()));
        for (const auto &arg : cmd.getArgs())
        {
            args.push_back(const_cast<char *>(arg.c_str()));
        }
        args.push_back(nullptr);

        if (execvp(args[0], args.data()) == -1)
        {
            std::cerr << "Error: Command not found" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        int status;
        if (waitpid(pid, &status, 0) == -1)
        {
            std::cerr << "Error: Waiting for child process failed" << std::endl;
        }
    }
}
