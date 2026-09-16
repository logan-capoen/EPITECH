/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** save
*/

#include "myworld.h"

static void convert_num(int num, char *buff, int *i)
{
    if (num == 0) {
        buff[*i] = '0';
        (*i)++;
    } else {
        while (num > 0) {
            buff[*i] = num % 10 + '0';
            (*i)++;
            num /= 10;
        }
    }
}

char *int_to_str_two(int num)
{
    char *buff = malloc(sizeof(char) * 12);
    int i = 0;
    int neg = (num < 0) ? 1 : 0;

    if (buff == NULL)
        return NULL;
    num = (neg) ? num * (-1) : num;
    for (int j = 0; j < 12; j++)
        buff[j] = '\0';
    convert_num(num, buff, &i);
    if (neg) {
        buff[i] = '-';
        i++;
    }
    buff[i] = '\0';
    return my_revstr(buff);
}

static void write_body(int size, int **map, int fd)
{
    char *buff = NULL;
    char space = ' ';
    char newline = '\n';

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            buff = int_to_str_two(map[y][x]);
            write(fd, buff, strlen(buff));
            free(buff);
            write(fd, &space, sizeof(char));
        }
        write(fd, &newline, 1);
    }
}

static void write_map(int fd, int **map, int size)
{
    char begin = 'B';
    char newline = '\n';
    char end = '\0';
    int tmp_rev = 0;
    char *buff = NULL;

    write(fd, "legend", 6);
    buff = int_to_str_two(size);
    write(fd, buff, strlen(buff));
    free(buff);
    write(fd, &begin, 1);
    write(fd, &newline, 1);
    write_body(size, map, fd);
    write(fd, &end, 1);
}

int save_map(world_t *world)
{
    int fd = -1;
    char path[PATH_MAX_LEN];
    int size = 0;

    file_explorer_save(path, PATH_MAX_LEN);
    if (*path == 0) {
        dprintf(1, "[OO] Canceled save\n");
        return 0;
    }
    if (access(path, F_OK) == 0) {
        fd = open(path, O_RDWR | O_TRUNC);
    } else
        fd = open(path, O_CREAT | O_RDWR, 00400 | 00200);
    write_map(fd, world->map, world->size);
    close(fd);
    dprintf(1, "[OK] Successfully saved map in '%s' !\n", path);
    return 0;
}
