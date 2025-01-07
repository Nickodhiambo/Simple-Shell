#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "main.h"

int main(int argc, char **argv)
{
    // Load configuration files, if any

    // Run command loop
    lsh_loop();

    // Perform shutdown/cleanup
    return EXIT_SUCCESS;
}

// Define command loop
void lsh_loop()
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);
    } while (status);

    free(line);
    free(args);
}

// Function that reads a line
#define LSH_RL_BUFSIZE 1024
char *lsh_read_line()
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    int c;
    char *buffer = malloc(sizeof(char) * bufsize);

    if (!buffer)
    {
        fprintf(stderr, "lsh: Allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        // Read a character
        c = getchar();

        // If we hit a EOF or new line, replace with null and return
        if (c == EOF || c == '\n')
        {
            buffer[position] = '\0';
            return buffer;
        }
        else
            buffer[position] = c;
        position++;

        // If we exceed the buffer, reallocate
        if (position >= bufsize)
        {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);

            // Check for realloc errors
            if (!buffer)
            {
                fprintf(stderr, "lsh: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Function to split command line
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

char **lsh_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0; // arg index in args array
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "lsh: Allocation error\n");
        exit(EXIT_FAILURE);
    }

    // split the command line into args
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens)
            {
                fprintf(stderr, "lsh: Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

// Create a process to run user commands
int lsh_launch(char **args)
{
    pid_t pid, wpid;
    int status;

    pid = fork(); // Duplicate a parent process to create a child

    if (pid == 0)
    {
        // Child process
        if (execvp(args[0], args) == -1)
            perror("lsh");
        exit(EXIT_FAILURE);
    }

    else if (pid < 0)
        // Error forking
        perror("lsh");

    else
    {
        // parent process
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

// Forward declarations for built in shell commands
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

// List of built-in commands followed by their corresponding functions
char *builtin_str[] = {
    "cd",
    "help",
    "exit"};

int (*builtin_func[])(char **) = {
    &lsh_cd,
    &lsh_help,
    &lsh_exit};

int lsh_num_builtins()
{
    return (sizeof(builtin_str) / sizeof(char *));
}

// Builtin function implementation
int lsh_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: Expected argument to \"cd\"\n");
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("lsh");
        }
    }
    return 1;
}

int lsh_help(char **args)
{
    printf("Nick Odhiambo's shell program\n");
    printf("Type a program and its arguments then hit enter\n");
    printf("The following are built-in functions:\n");

    for (int i = 0; i < lsh_num_builtins(); i++)
        printf("    %s\n", builtin_str[i]);

    printf("Use the man command for info on other programs\n");
    return 1;
}

int lsh_exit(char **args)
{
    return 0;
}

int lsh_execute(char **args)
{
    if (args[0] == NULL)
        // User enters no command, a whitespace or empty string
        return 1;
    for (int i = 0; i < lsh_num_builtins(); i++)
    {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }
    return lsh_launch(args);
}