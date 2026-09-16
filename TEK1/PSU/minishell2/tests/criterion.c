/*
** EPITECH PROJECT, 2025
** criterion_workshop
** File description:
** criterion
*/


#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int open_utils(int *stdout_fd, int *output_fd) 
{
    *stdout_fd = dup(STDOUT_FILENO);
    *output_fd = open("test_file.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);

    if (*output_fd == -1)
        return -1;
    dup2(*output_fd, STDOUT_FILENO);
    return 0;
}

int close_utils(const int *stdout_fd, const int *output_fd) 
{
    fflush(stdout);
    if (*output_fd != -1)
        close(*output_fd);
    dup2(*stdout_fd, STDOUT_FILENO);
    close(*stdout_fd);
    close(*output_fd);
    return 0;
}

char *get_file_content(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    struct stat file;
    char *buffer = NULL;
    size_t size = 0;

    lstat(filename, &file);
    buffer = malloc(sizeof(char) * (file.st_size + 1));
    size = read(fd, buffer, sizeof(buffer));
    buffer[size] = '\0';
    return buffer;
}
