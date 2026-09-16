/*
** EPITECH PROJECT, 2025
** robotfactory
** File description:
** open
*/

/**
 * @file open.c
 * @brief Open the given '.s' file and create '.cor' file
 *
 * Check if the given file exists. Check its extension.
 * Create the cor file with the right permissions.
 * Format the main buffer before parsing it.
 */

#include "op.h"

/**
 * @brief Check if the file extension is '.s'
 *
 * @param *filename The given file name
 * @return int A boolean to say whether the extension is respected or not.
 */
int check_extension(char *filename)
{
    int len = my_strlen(filename);

    if (my_strncmp(filename + (len - 2), ".s", 2) == 0)
        return 1;
    return 0;
}

/**
 * @brief Check and open the given file
 *
 * @param ac The number of cli args
 * @param **av The array of cli args
 * @return int A status code to indicate if opening was a success
 */
int open_file(int ac, char **av)
{
    int fd = -1;

    if (ac != 2)
        return -1;
    if (check_extension(av[1]))
        fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return -1;
    return fd;
}

/**
 * @brief Create the cor file from the s file
 *
 * @param **av The array of cli args
 * @return int -1 is creation failed or the file descriptor is success
 */
int create_cor(char **av)
{
    int len = my_strlen(av[1]);
    char *cor_file = malloc(sizeof(char) * len + 2);
    int fd_cor = -1;

    if (cor_file == NULL)
        return -1;
    cor_file[0] = 0;
    my_strcpy(cor_file, av[1]);
    cor_file[len - 2] = 0;
    my_strcat(cor_file, ".cor");
    fd_cor = open(cor_file, O_CREAT | O_RDWR, 00700 | 00070 | 00007);
    free(cor_file);
    return fd_cor;
}

/**
 * @brief Get and format the content of the s file
 *
 * @param ac The number of cli args
 * @param **av The array of cli args
 * @return char* The pointer to the buffer, NULL if failed
 */
char *create_buffer(int ac, char **av)
{
    int fd_s = -1;
    char *buff = NULL;
    int result_quote = 0;
    char *final_buff = NULL;
    int file_size = get_size(av[1]);

    fd_s = open_file(ac, av);
    if (fd_s == -1 || file_size == -1)
        return NULL;
    buff = malloc(sizeof(char) * (file_size + 1));
    if (!buff)
        return NULL;
    read(fd_s, buff, file_size);
    final_buff = remove_comments(buff);
    result_quote = check_wrong_quotes(final_buff);
    if (result_quote == 1 || result_quote == -1)
        return NULL;
    close(fd_s);
    return final_buff;
}
