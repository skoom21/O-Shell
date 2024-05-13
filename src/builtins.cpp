#include "builtins.h"

bool Builtins::isBuiltin(const std::string& name) {   
    return name == "cd" || name == "ls" || name == "mkdir" || name == "rm" || name == "pwd" || name == "echo" || name == "help";
}

void Builtins::execute(const Command& cmd) {
    
    try {
        if (cmd.getName() == "cd") {
            
            if (cmd.getArgs().size() != 1) {
                throw std::invalid_argument("Usage: cd <directory>");
            }
            if (chdir(cmd.getArgs()[0].c_str()) != 0) {
                throw std::runtime_error("Failed to change directory");
            }
        } else if (cmd.getName() == "ls") {
            const char* directory = ".";
            bool longFormat = false;
            bool allFiles = false;
            
            
            for (const auto& arg : cmd.getArgs()) {
                if (arg == "-l") {
                    longFormat = true;
                } else if (arg == "-a") {
                    allFiles = true;
                } else if (arg[0] == '-') {
                    throw std::invalid_argument("Invalid option: " + arg);
                } else {
                    directory = arg.c_str();
                }
            }
            
            DIR* dir = opendir(directory);
            if (dir == nullptr) {
                throw std::runtime_error("Failed to open directory");
            }
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                
                if (!allFiles && entry->d_name[0] == '.') {
                    continue;
                }
                
                if (longFormat) {
                    
                    struct stat fileStat;
                    std::string filePath = std::string(directory) + "/" + entry->d_name;
                    if (stat(filePath.c_str(), &fileStat) == -1) {
                        throw std::runtime_error("Failed to get file details");
                    }
                    
                    std::cout << entry->d_name << " ";
                    std::cout << (S_ISDIR(fileStat.st_mode) ? "d" : "-");
                    std::cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
                    std::cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
                    std::cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
                    std::cout << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
                    std::cout << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
                    std::cout << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
                    std::cout << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
                    std::cout << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
                    std::cout << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
                    std::cout << " " << fileStat.st_uid << " " << fileStat.st_gid << " ";
                    std::cout << fileStat.st_size << " ";
                    std::cout << entry->d_name << std::endl;
                } else {
                    std::cout << entry->d_name << "   ";
                }
            }
            closedir(dir);
        } else if (cmd.getName() == "mkdir") {
            
            if (cmd.getArgs().size() != 1) {
                throw std::invalid_argument("Usage: mkdir <directory>");
            }
            if (mkdir(cmd.getArgs()[0].c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
                throw std::runtime_error("Failed to create directory");
            }
        } else if (cmd.getName() == "rm") {
            
            if (cmd.getArgs().size() != 1) {
                throw std::invalid_argument("Usage: rm <file_or_directory>");
            }
            if (remove(cmd.getArgs()[0].c_str()) != 0) {
                throw std::runtime_error("Failed to remove file or directory");
            }
        } else if (cmd.getName() == "pwd") {
            
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) == nullptr) {
                throw std::runtime_error("Failed to get current working directory");
            }
            std::cout << cwd << std::endl;
        } else if (cmd.getName() == "echo") {
            
            for (const auto& arg : cmd.getArgs()) {
                std::cout << arg << " ";
            }
            std::cout << std::endl;
        } else if (cmd.getName() == "help") {
            
            std::cout << "Available built-in commands:" << std::endl;
            std::cout << "cd <directory>                  Change directory" << std::endl;
            std::cout << "ls [-l] [-a] [directory]        List files in the current or specified directory" << std::endl;
            std::cout << "mkdir <directory>               Create a new directory" << std::endl;
            std::cout << "rm <file_or_directory>          Remove file or directory" << std::endl;
            std::cout << "pwd                             Print current working directory" << std::endl;
            std::cout << "echo <args>                     Print arguments" << std::endl;
            std::cout << "help                            Display this help message" << std::endl;
        } else {
            
            throw std::invalid_argument("Unknown builtin command");
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}
