# Minishell - As Beautiful as a Shell

![Minishell](link)

Minishell is a simple command-line interpreter project inspired by bash. It provides an opportunity to understand how shells work by implementing fundamental features such as command parsing, execution, piping, redirections, and signal handling. Through this project, you’ll gain a deeper understanding of processes, file descriptors, and memory management in C.

## Project Purpose

The purpose of this project is to:
- Learn about process management in Unix systems.
- Understand how shells handle commands, pipelines, and redirections.
- Explore file descriptor management for input/output redirection.
- Implement signal handling and built-in shell commands.
- Adhere to strict coding norms and minimize memory leaks.

This project challenges you to replicate essential functionalities of a shell, equipping you with knowledge that applies to various areas of systems programming.

## Features and Requirements

### Mandatory Features
1. **Interactive Shell Prompt**:
   - Display a prompt when waiting for user input.
   - Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` to mimic bash behavior:
     - `ctrl-C`: Displays a new prompt on a new line.
     - `ctrl-D`: Exits the shell.
     - `ctrl-\`: Does nothing.

2. **Command Execution**:
   - Search and execute commands using the `PATH` environment variable or relative/absolute paths.

3. **Quotes Handling**:
   - Single quotes (`'`): Prevent interpretation of metacharacters within.
   - Double quotes (`"`): Prevent interpretation except for `$` (dollar sign).

4. **Redirections**:
   - `<`: Redirect input.
   - `>`: Redirect output.
   - `<<`: Here-document with a delimiter.
   - `>>`: Redirect output in append mode.

5. **Pipes**:
   - Implement pipelines (`|`), connecting the output of one command to the input of the next.

6. **Environment Variables**:
   - Handle `$` for variable expansion.
   - Handle `?` to expand the exit status of the last executed command.

7. **Built-in Commands**:
   - `echo` with `-n` option.
   - `cd` with relative or absolute paths.
   - `pwd` with no options.
   - `export` with no options.
   - `unset` with no options.
   - `env` with no options or arguments.
   - `exit` with no options.

8. **Memory Management**:
   - Ensure proper cleanup of heap-allocated memory. No memory leaks allowed in your code.

### Bonus Features
- Implement logical operators (`&&` and `||`) with parentheses for precedence.
- Wildcard (`*`) handling for the current directory.

> **Note**: Bonus features will only be evaluated if all mandatory requirements are met perfectly.

---

## Roles and Guidelines

### General Rules
- Code must be written in C and follow the **42 Norm**.
- Use only allowed external functions (e.g., `readline`, `printf`, `fork`, `execve`, `pipe`).
- Use a single global variable, limited to signal number storage.
- Manage all errors gracefully (no segmentation faults, bus errors, etc.).
- Use a Makefile with the following rules:
  - `all`, `clean`, `fclean`, `re`, and `bonus`.
- If using `libft`, include its source code and Makefile in a `libft/` folder.

### Restrictions
- Avoid interpreting unclosed quotes or unsupported special characters like `\` or `;`.
- Stick strictly to the subject's requirements and use bash as a reference for doubts.

---

## Steps to Implementation

1. **Initialize the Project**:
   - Set up the repository and include necessary files (`Makefile`, `.h`, `.c`).
   - Include `libft` if needed.

2. **Implement the Shell Core**:
   - Create a loop to display a prompt and wait for user input.
   - Parse commands and handle syntax errors.

3. **Add Command Execution**:
   - Implement searching for executables in `PATH`.
   - Execute commands using `fork` and `execve`.

4. **Handle Quotes and Redirections**:
   - Parse single and double quotes properly.
   - Add support for `<`, `>`, `<<`, and `>>` redirections.

5. **Implement Pipes**:
   - Create pipelines using `pipe()` to link commands.

6. **Add Built-in Commands**:
   - Implement built-ins like `echo`, `cd`, `pwd`, etc., according to specifications.

7. **Handle Signals**:
   - Capture and handle signals (`SIGINT`, `SIGQUIT`, etc.) to mimic bash behavior.

8. **Memory Management**:
   - Ensure all heap allocations are freed and avoid memory leaks.

9. **Bonus Features** (if applicable):
   - Implement `&&`, `||`, and wildcard handling.

---

## Compilation and Testing

### Compile the Shell
Run the following command to compile the project:
```bash
make
