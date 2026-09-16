/*
** EPITECH PROJECT, 2025
** cd_functions
** File description:
** cd tilde
*/

/**
 * @file get_home_user.c
 * @brief Functions to retrieve a user's home directory.
 *
 * This file contains functions to parse the `/etc/passwd` file and extract
 * the home directory of a specified user.
 */
#include "builtins.h"

/**
 * @brief Reads the content of the `/etc/passwd` file.
 *
 * This function opens the `/etc/passwd` file, reads its content into a buffer,
 * and returns the buffer as a null-terminated string.
 *
 * @return A dynamically allocated string containing the file content, or NULL
 *         if an error occurs.
 */
static char *read_passwd_file(void)
{
    int fd = open("/etc/passwd", O_RDONLY);
    char *buffer = NULL;
    int bytes_read = 0;

    if (fd == -1)
        return NULL;
    buffer = malloc(BUFFER_SIZE);
    if (!buffer) {
        close(fd);
        return NULL;
    }
    bytes_read = read(fd, buffer, BUFFER_SIZE - 1);
    close(fd);
    if (bytes_read <= 0) {
        free(buffer);
        return NULL;
    }
    buffer[bytes_read] = '\0';
    return buffer;
}

/**
 * @brief Finds the line corresponding to a specific user in the buffer.
 *
 * This function searches for a line in the `/etc/passwd` file buffer that
 * matches the specified username.
 *
 * @param buffer The content of the `/etc/passwd` file.
 * @param user The username to search for.
 * @return A dynamically allocated string containing the matching line, or NULL
 *         if the user is not found.
 */
static char *find_user_line(char *buffer, const char *user)
{
    char *saveptr = NULL;
    char *copy = strdup(buffer);
    char *line_start = copy;
    char *temp = NULL;
    char *username = NULL;
    char *line = strtok_r(line_start, "\n", &saveptr);

    while ((line)) {
        line_start = NULL;
        temp = strdup(line);
        username = strtok(temp, ":");
        if (username && strcmp(username, user) == 0) {
            free(temp);
            return strdup(line);
        }
        free(temp);
        line = strtok_r(line_start, "\n", &saveptr);
    }
    free(copy);
    return NULL;
}

/**
 * @brief Extracts a specific field from a line in the `/etc/passwd` file.
 *
 * This function splits a line from the `/etc/passwd` file into fields
 * separated by colons (`:`) and returns the field at the specified index.
 *
 * @param line The line from the `/etc/passwd` file.
 * @param field_index The index of the field to extract (0-based).
 * @return A dynamically allocated string containing the field, or NULL if the
 *         field does not exist.
 */
static char *extract_field(char *line, int field_index)
{
    char *copy = strdup(line);
    char *token = NULL;
    char *result = NULL;

    token = strtok(copy, ":");
    for (int i = 0; i < field_index && token; i++) {
        token = strtok(NULL, ":");
    }
    result = token ? strdup(token) : NULL;
    free(copy);
    return result;
}

/**
 * @brief Retrieves the home directory of a specified user.
 *
 * This function reads the `/etc/passwd` file, searches for the specified user,
 * and extracts their home directory from the corresponding line.
 *
 * @param user The username whose home directory is to be retrieved.
 * @return A dynamically allocated string containing the user's home directory,
 *         or NULL if the user is not found or an error occurs.
 */
char *get_root_home(char *user)
{
    char *buffer = read_passwd_file();
    char *line = NULL;
    char *home_dir = NULL;

    if (!buffer || !user)
        return NULL;
    line = find_user_line(buffer, user);
    free(buffer);
    if (!line)
        return NULL;
    home_dir = extract_field(line, 5);
    free(line);
    return home_dir;
}
