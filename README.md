# Simple Linux Shell

## Overview
This project is a simple Linux shell implemented in C. It provides a minimal command-line interface for users to execute commands and interact with the operating system. The shell supports a variety of built-in commands and allows users to direct output to either a file or the standard output.

---

## Features

### Built-in Commands
The shell includes the following built-ins:

1. **cd**: Change the current working directory.
   - Usage: `cd <directory>`
   - Example: `cd /home/user`

2. **help**: Display information about the shell and its built-in commands.
   - Usage: `help`
   - Example: `help`

3. **exit**: Terminate the shell.
   - Usage: `exit`
   - Example: `exit`

4. **env**: Display the current environment variables.
   - Usage: `env`
   - Example: `env`

5. **setenv**: Set or update an environment variable.
   - Usage: `setenv <variable> <value>`
   - Example: `setenv PATH /usr/local/bin`

6. **unsetenv**: Remove an environment variable.
   - Usage: `unsetenv <variable>`
   - Example: `unsetenv PATH`

7. **echo**: Display a string or environment variable value. Supports redirection to a file or stdout.
   - Usage:
     - `echo <message>`: Print to stdout.
     - `echo <message> > <file>`: Redirect output to a file.
     - `echo <message> >> <file>`: Append output to a file.
   - Example:
     - `echo Hello, World!`
     - `echo Hello, World! > output.txt`

### Other Features
- **Environment Variable Handling**: Supports setting, unsetting, and viewing environment variables.
- **Output Redirection**: The `echo` command allows output redirection using `>` and `>>`.
- **Robust Error Handling**: Detects and reports errors such as invalid commands, missing arguments, and permission issues.

---

## How to Build and Run

1. Clone or download the project source code locally.
   ```bash
   git clone https://github.com/Nickodhiambo/Simple-Shell.git
   
2. Compile the source code using `gcc`:
   ```bash
   gcc -o simple_shell main.c
   ```
4. Run the shell:
   ```bash
   ./simple_shell
   ```

---

## Usage

Once the shell is running, you can interact with it by typing commands at the prompt. For example:

- To change the directory:
  ```bash
  cd /path/to/directory
  ```
- To view environment variables:
  ```bash
  env
  ```
- To set an environment variable:
  ```bash
  setenv MY_VAR value
  ```
- To display a message:
  ```bash
  echo "Hello, World!"
  ```

Type `help` to view a list of available commands and their usage.

---

## Code Structure

The project is structured as follows:
- **main.c**: Contains the entry point of the program and the main shell loop.
- **main.h**: Contains all the function definitions

---

## Limitations

- The shell does not support complex command chaining (e.g., pipes `|` or `&&`).
- Background processes (e.g., `command &`) are not implemented.
- Limited error messages for some invalid operations.

---

## Future Enhancements

- Add support for piping and background processes.
- Improve error reporting and debugging information.
- Implement additional built-in commands such as `history`.
- Support command-line completion and history.

---

## Contribution
Contributions are welcome! Feel free to fork the repository and submit pull requests. Ensure your code adheres to the project's coding style and includes appropriate comments and documentation.

---

## License
This project is licensed under the MIT License. See the LICENSE file for details.

---

## Acknowledgments
This project was inspired by the need to understand fundamental operating system concepts such as process management, environment variables, and input/output redirection.

