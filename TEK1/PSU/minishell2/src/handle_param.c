/*
** EPITECH PROJECT, 2025
** minishell2
** File description:
** handle_param
*/

#include "minishell2.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "my.h"
#include <stdio.h>
#include <sys/wait.h>

char *start_line(char *line)
{
    for (int i = 0; line[i] == ' ' || line[i] == '\t'; i++)
        line++;
    return line;
}

static int handle_right_redirection(char *outputs)
{
    int fd = 0;
    int save = dup(1);

    if (outputs[my_strlen(outputs) - 1] == ' ') {
        outputs[my_strlen(outputs) - 1] = '\0';
        fd = open(outputs, O_CREAT | O_RDWR | O_APPEND, 0644);
    } else
        fd = open(outputs, O_CREAT | O_RDWR | O_TRUNC, 0644);
    dup2(fd, 1);
    return save;
}

static int handle_left_redirection(char *input)
{
    int fd = 0;
    int save = 0;

    if (access(input, F_OK) == -1) {
        my_putstr(input);
        my_putstr(": No such file or directory.\n");
        return -2;
    }
    save = dup(0);
    fd = open(input, O_RDONLY);
    dup2(fd, 0);
    return save;
}

static void close_pipe_and_wait(int pipefd[2],
    pid_t pid1, pid_t pid2, int *status)
{
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, &(status[0]), 0);
    waitpid(pid2, &(status[1]), 0);
}

static void handle_second_command(int pipefd[2],
    input_t *inputs, env_t *env_list, char **lwd)
{
    close(pipefd[1]);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    exit(parsing_input(start_line(inputs->pipes[inputs->index]),
        env_list, lwd));
}

static void handle_first_command(int pipefd[2], input_t *inputs,
    env_t *env_list, char **lwd)
{
    close(pipefd[0]);
    dup2(pipefd[1], STDOUT_FILENO);
    close(pipefd[1]);
    exit(parsing_input(start_line(inputs->lines[inputs->index]),
        env_list, lwd));
}

int execute_pipe(input_t *inputs, env_t *env_list, char **lwd)
{
    int pipefd[2];
    pid_t pid1 = 0;
    pid_t pid2 = 0;
    int status[2] = {0};

    if (pipe(pipefd) == -1)
        return -1;
    pid1 = fork();
    if (pid1 == -1)
        return -1;
    if (pid1 == 0)
        handle_first_command(pipefd, inputs, env_list, lwd);
    pid2 = fork();
    if (pid2 == -1)
        return -1;
    if (pid2 == 0)
        handle_second_command(pipefd, inputs, env_list, lwd);
    close_pipe_and_wait(pipefd, pid1, pid2, status);
    return WEXITSTATUS(status[1]);
}

int check_params(input_t *inputs, env_t *env_list, char **lwd, int is_pipe)
{
    int status = 0;
    int save_input = -1;
    int save_output = -1;
    int i = inputs->index;

    if (inputs->inputs[i] != NULL && inputs->pipes[i] != NULL)
        return 1;
    if (is_pipe)
        return execute_pipe(inputs, env_list, lwd);
    if (inputs->outputs[i] != NULL)
        save_output = handle_right_redirection(inputs->outputs[i]);
    if (inputs->inputs[i] != NULL)
        save_input = handle_left_redirection(inputs->inputs[i]);
    if (save_input != -2)
        status = parsing_input(start_line(inputs->lines[i]), env_list, lwd);
    if (save_input != -1)
        dup2(save_input, 0);
    if (save_output != -1)
        dup2(save_output, 1);
    return status;
}
