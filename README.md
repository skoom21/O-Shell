# O-Shell

<img src="./img/logo.png" align="right" width="256" height="256" style="margin: 0 10px">

Welcome to O-Shell, your interactive command-line shell project! O-Shell aims to provide a user-friendly interface for interacting with your operating system through the command line.

## Features

- **Interactive Shell:** O-Shell offers an interactive command-line interface, allowing users to execute commands and navigate the file system efficiently.

- **Tab Completion:** Enjoy the convenience of tab completion, which suggests file and directory names as you type, making command entry faster and more intuitive.

- **Customization:** Customize your shell with different themes and configurations to suit your preferences and workflow.

## Dependencies

- **Make:** The `make` utility is required to build the shell using the provided Makefile. If `make` is not installed, you can install it using the package manager of your operating system:
  - **For Debian/Ubuntu:**
    ```
    sudo apt-get install make
    ```
  - **For CentOS/RHEL:**
    ```
    sudo yum install make
    ```
  - **For macOS (via Homebrew):**
    ```
    brew install make
    ```

- **Readline Library:** O-Shell utilizes the Readline library for advanced line-editing and command-line interaction features. Ensure that the Readline library is installed on your system before building the shell. You can install it using the package manager of your operating system:
  - **For Debian/Ubuntu:**
    ```
    sudo apt-get install libreadline-dev
    ```
  - **For CentOS/RHEL:**
    ```
    sudo yum install readline-devel
    ```
  - **For macOS (via Homebrew):**
    ```
    brew install readline

## Built-in Commands

O-Shell supports the following built-in commands:

- **cd:** Change the current directory.
- **ls:** List files and directories in the current directory.
- **rm:** Remove files or directories.
- **pwd:** Print the current working directory.
- **mkdir:** Create a new directory.
- **echo:** Display a line of text.
- **help:** Show support for all the built-in commands and their usage.

## Getting Started

To use O-Shell, follow these simple steps:

1. Clone the repository:
git clone https://github.com/yourusername/o-shell.git


2. Navigate to the project directory:
cd o-shell



3. Build the shell using the provided Makefile:
make

4. Run the shell executable:
./main

## Contributing

Contributions to O-Shell are welcome! If you'd like to contribute, please fork the repository, make your changes, and submit a pull request. Make sure to follow the project's coding standards and guidelines.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Special thanks to Robot Ahmed Shah for inspiration and guidance.
