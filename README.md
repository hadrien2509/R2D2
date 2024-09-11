# R2D2 - Minishell

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](https://github.com/username/minishell)
[![Version](https://img.shields.io/badge/version-1.0.0-blue.svg)](https://github.com/username/minishell/releases)

R2D2 is a custom implementation of a Unix shell, written in C as part of the 42 School curriculum. This project aims to recreate the basic functionalities of a shell, including command execution, pipelines, redirections, and environment variable management.

## Table of Contents

- [Project Overview](#project-overview)
- [How to Run the Project](#how-to-run-the-project)
- [Project Structure](#project-structure)
- [Main Features](#main-features)
- [Front-end Logic](#front-end-logic)
- [Back-end Logic](#back-end-logic)
- [Contribution Guidelines](#contribution-guidelines)
- [License](#license)
- [Additional Resources](#additional-resources)
- [Contact Information](#contact-information)

## Project Overview

R2D2 is a Unix shell that provides a command-line interface for interacting with the operating system. It supports various features such as command execution, pipelines, redirections, environment variable management, and built-in commands like `cd`, `echo`, `export`, and `unset`.

The project aims to deepen the understanding of process creation, execution, and management in Unix-like systems. It also covers topics like signal handling, file descriptors, and memory management.

## How to Run the Project

To run the R2D2 shell, follow these steps:

1. Clone the repository: `git clone https://github.com/username/minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Compile the project: `make`
4. Run the shell: `./minishell`

Once the shell is running, you can enter commands just like in a regular Unix shell. Use `exit` or press `Ctrl+D` to quit the shell.

### Prerequisites

- GCC (GNU Compiler Collection)
- GNU Make
- Readline library

### Running Tests

To run the test suite, execute the following command:

```bash
make test
```

## Project Structure

```
/Volumes/Storage/goinfre/hgeissle/R2D2
├── README.md
├── .git/
├── libft/
├── minishell_tester/
├── srcs/
└── includes/
    ├── minishell.h
    └── token.h
```

- `README.md`: This file, containing project documentation.
- `.git/`: Git repository files.
- `libft/`: Custom C library with various utility functions.
- `minishell_tester/`: Directory containing test scripts for the shell.
- `srcs/`: Source code files for the shell implementation.
- `includes/`: Header files for the project.
  - `minishell.h`: Main header file with function declarations and data structures.
  - `token.h`: Header file for token-related data structures and functions.

## Main Features

- Command execution
- Pipelines
- Input/Output redirections (`<`, `>`, `>>`, `<<`)
- Environment variable management (`export`, `unset`)
- Built-in commands (`cd`, `echo`, `env`, `exit`, `pwd`)
- Signal handling (`Ctrl+C`, `Ctrl+\`)
- Command history and line editing (via Readline library)

## Front-end Logic

The front-end of R2D2 is responsible for user input handling and display. It utilizes the GNU Readline library for line editing and command history management. The main components of the front-end include:

- **Input Handling**: The shell prompts the user for input and reads commands from the terminal.
- **Command Parsing**: User input is parsed and tokenized into individual commands, arguments, and control operators (e.g., pipes, redirections).
- **Command Execution**: Parsed commands are executed by forking child processes and executing the corresponding programs or built-in commands.
- **Output Display**: The output of executed commands is displayed in the terminal.

## Back-end Logic

The back-end of R2D2 handles the core shell functionality, including process management, signal handling, and environment variable management. Key components include:

- **Process Management**: The shell creates child processes for executing commands, manages pipelines, and handles process termination and signal propagation.
- **Signal Handling**: The shell handles signals such as `SIGINT` (`Ctrl+C`) and `SIGQUIT` (`Ctrl+\`) for graceful termination and job control.
- **Environment Variables**: The shell maintains an environment variable list and provides functionality for setting, unsetting, and retrieving environment variables.
- **Built-in Commands**: The shell implements built-in commands like `cd`, `echo`, `export`, and `unset` directly within the shell process.
- **File Descriptors and Redirections**: The shell manages file descriptors and handles input/output redirections for commands.

## Contribution Guidelines

Contributions to the R2D2 project are welcome! If you encounter any issues or have ideas for improvements, please open an issue on the GitHub repository. If you'd like to contribute code, follow these steps:

1. Fork the repository
2. Create a new branch for your feature or bug fix
3. Make your changes and commit them with descriptive commit messages
4. Push your changes to your forked repository
5. Submit a pull request to the main repository

Please ensure that your code adheres to the project's coding style and conventions.

## License

This project is licensed under the [MIT License](LICENSE).

## Additional Resources

- [Unix Shell Programming](https://en.wikipedia.org/wiki/Unix_shell#Shell_programming): Wikipedia article on Unix shell programming.
- [Advanced Unix Programming with Linux](https://courses.cs.vt.edu/cs5204/): Virginia Tech course on advanced Unix programming concepts.
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html): Documentation for the GNU Readline library used in this project.

## Contact Information

If you have any questions, suggestions, or need further assistance, please feel free to reach out:

- Email: [your_email@example.com](mailto:your_email@example.com)
- GitHub: [@your_username](https://github.com/your_username)