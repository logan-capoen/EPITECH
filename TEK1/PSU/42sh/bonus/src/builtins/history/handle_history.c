/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** handle_history
*/

/**
 * @file handle_history.c
 * @brief Functions to manage the shell's command history.
 *
 * This file contains all the functions required to handle the shell's
 * history, including adding commands, displaying the history, and
 * executing commands from the history.
 */

#include "builtins.h"
#include "exec.h"

/**
 * @brief Free a partially filled history.
 *
 * This function frees the memory allocated for a partially filled
 * history array, up to the specified count.
 *
 * @param history The history array.
 * @param count Number of valid entries to free.
 */
void free_history(char **history, int count)
{
    for (int i = 0; i < count && history && history[i]; i++)
        free(history[i]);
    if (history)
        free(history);
}

/**
 * @brief Add a command to the history array.
 *
 * This function adds a new command to the history array. If the
 * reallocation fails, it frees the existing history and returns an error.
 *
 * @param history_ptr Pointer to the history array.
 * @param shell The shell structure containing the history size.
 * @param line The command to add to the history.
 * @return 0 on success, 1 on failure.
 */
static int add_command_to_history(char ***history_ptr,
    shell_t *shell, char *line)
{
    char **tmp = realloc(*history_ptr, sizeof(char *)
        * (shell->history_size + 2));

    if (!tmp) {
        free(line);
        free_history(*history_ptr, shell->history_size);
        return 1;
    }
    *history_ptr = tmp;
    (*history_ptr)[shell->history_size] = strdup(line);
    if (!(*history_ptr)[shell->history_size]) {
        free(line);
        free_history(*history_ptr, shell->history_size);
        return 1;
    }
    return 0;
}

/**
 * @brief Load the history from a file.
 *
 * This function reads the history from the `.42sh_history` file and
 * populates the shell's history array.
 *
 * @param fd The file descriptor of the `.42sh_history` file.
 * @param shell The shell structure containing the history.
 * @return A dynamically allocated history array, or NULL on failure.
 */
static char **file_to_history(FILE *fd, shell_t *shell)
{
    char **history = malloc(sizeof(char *));
    char *line = NULL;
    size_t size = 0;

    if (!history)
        return NULL;
    for (; getline(&line, &size, fd) != -1; shell->history_size++) {
        line[strcspn(line, "\n")] = '\0';
        if (add_command_to_history(&history, shell, line))
            return NULL;
    }
    free(line);
    history[shell->history_size] = NULL;
    return history;
}

/**
 * @brief Open the history file.
 *
 * This function opens the `.42sh_history` file in the specified mode.
 *
 * @param shell The shell structure containing environment variables.
 * @param params The mode to open the file (e.g., "r" or "a").
 * @return A file descriptor for the history file, or NULL on failure.
 */
static FILE *get_fd(shell_t *shell, char *params)
{
    char *home = get_value_key("HOME", shell->env->global);
    char *pathfile = NULL;
    FILE *fd = NULL;

    if (home) {
        pathfile = strjoin(home, "/.42sh_history");
        fd = fopen(pathfile, params);
        free(pathfile);
        free(home);
    }
    return fd;
}

/**
 * @brief Load the history into the shell.
 *
 * This function loads the history from the `.42sh_history` file into
 * the shell's history array.
 *
 * @param shell The shell structure containing the history.
 */
void get_history(shell_t *shell)
{
    FILE *fd = get_fd(shell, "r");

    if (!fd)
        return;
    shell->history = file_to_history(fd, shell);
    fclose(fd);
}

/**
 * @brief Reset the history when it exceeds the size limit.
 *
 * This function frees all entries in the history and resets the
 * history size to 0.
 *
 * @param shell The shell structure containing the history.
 */
static void reset_history(shell_t *shell)
{
    for (int i = 0; i < shell->history_size; i++)
        free(shell->history[i]);
    free(shell->history);
    shell->history = NULL;
    shell->history_size = 0;
}

/**
 * @brief Add a command to the history and save it to the file.
 *
 * This function adds a command to the shell's history array and appends
 * it to the `.42sh_history` file.
 *
 * @param command The command to add to the history.
 * @param shell The shell structure containing the history.
 */
void add_to_history(char *command, shell_t *shell)
{
    FILE *fd = get_fd(shell, "a");
    char **tmp = NULL;

    if (!fd)
        return;
    if (shell->history_size > 10000)
        reset_history(shell);
    tmp = realloc(shell->history, sizeof(char *) * (shell->history_size + 2));
    shell->history = tmp;
    shell->history[shell->history_size] = strdup(command);
    if (!shell->history[shell->history_size] || !tmp) {
        fclose(fd);
        return;
    }
    fprintf(fd, "%s\n", shell->history[shell->history_size]);
    shell->history_size += 1;
    shell->history[shell->history_size] = NULL;
    fclose(fd);
}

/**
 * @brief Display the entire history.
 *
 * This function prints the entire history with an index for each command.
 *
 * @param shell The shell structure containing the history.
 * @param command Unused parameter.
 * @param local Unused parameter.
 * @return Always returns 0.
 */
int display_history(shell_t *shell, __attribute_maybe_unused__ char **command,
    __attribute_maybe_unused__ int local)
{
    for (int i = 0; i < shell->history_size; i++)
        printf("%i %s\n", i + 1, shell->history[i]);
    return 0;
}

/**
 * @brief Execute a command from the history.
 *
 * This function searches the history for a command matching the given
 * input and returns it for execution.
 *
 * @param shell The shell structure containing the history.
 * @param command The input string specifying the command to execute.
 * @return A string containing the command from the history,
 * or NULL if not found.
 */
char *exec_history(shell_t *shell, char *command)
{
    int index;

    index = atoi(command + 1);
    if (index > 0 && index - 1 <= shell->history_size)
        return strdup(shell->history[index - 1]);
    for (int i = 0; i < shell->history_size; i++) {
        if (strncmp(command + 1, shell->history[i],
            strlen(command) - 1) == 0)
            return strdup(shell->history[i]);
    }
    printf("%s: Event not found.\n", command + 1);
    return NULL;
}
