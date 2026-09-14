/*
** EPITECH PROJECT, 2024
** handling_l_flag.c
** File description:
** handle for the l flag
*/
#include "include/my_ls.h"
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include "include/printf.h"
#include <pwd.h>
#include <grp.h>
#include "include/my.h"
#include <linux/limits.h>

static int display_permissions_usr_grp(mode_t mode)
{
    my_printf((mode & S_IRUSR) ? "r" : "-");
    my_printf((mode & S_IWUSR) ? "w" : "-");
    my_printf((mode & S_IXUSR) ? "x" : "-");
    my_printf((mode & S_IRGRP) ? "r" : "-");
    my_printf((mode & S_IWGRP) ? "w" : "-");
    my_printf((mode & S_IXGRP) ? "x" : "-");
    my_printf((mode & S_IROTH) ? "r" : "-");
    my_printf((mode & S_IWOTH) ? "w" : "-");
    return 0;
}

static int display_permissions(mode_t mode)
{
    if (S_ISDIR(mode))
        my_printf("d");

/**
 * @brief if function documentation
 * @return else Description of the return value
 */    else if (S_ISLNK(mode))
        my_printf("l");

/**
 * @brief my_printf function documentation
 * @return else Description of the return value
 */    else
        my_printf("-");
    display_permissions_usr_grp(mode);
    if ((mode & __S_ISVTX) && (mode & S_IXOTH))
        my_printf("t. ");

/**
 * @brief if function documentation
 * @param __S_ISVTX Description of __S_ISVTX
 * @return else Description of the return value
 */    else if (mode & __S_ISVTX)
        my_printf("T. ");

/**
 * @brief my_printf function documentation
 * @param S_IXOTH Description of S_IXOTH
 * @return else Description of the return value
 */    else
        my_printf((mode & S_IXOTH) ? "x. " : "-. ");
    return 0;
}

static int display_size_file(int size, int max_size_len)
{
    int len = my_len_int(size);

    for (int i = 0; i < max_size_len + 1 - len; i++)
        my_printf(" ");
    my_put_nbr(size);
    my_printf(" ");
    return 0;
}

static int display_date(char *time)
{
    time[16] = '\0';
    my_putstr(time + 4);
    my_printf(" ");
    return 0;
}

char *handle_buff(char *pathfile, char *data_file_name)
{
    char *buff = malloc(sizeof(char) * PATH_MAX);

    for (int i = 0; i < PATH_MAX - 1; i++)
        buff[i] = 0;
    buff[0] = '\0';
    my_strcat(buff, pathfile);
    if (pathfile[my_strlen(pathfile)] != '/')
        my_strcat(buff, "/");
    my_strcat(buff, data_file_name);
    return buff;
}

static int display_l_flag(struct dirent *data_file,
    int max_size_len, char *pathfile)
{
    struct stat sf;
    char *buff = handle_buff(pathfile, data_file->d_name);

    stat(buff, &sf);
    display_permissions(sf.st_mode);
    my_put_nbr((int)sf.st_nlink);
    my_printf(" ");
    my_putstr(my_strdup(getpwuid(sf.st_uid)->pw_name));
    my_printf(" ");
    my_putstr(my_strdup(getgrgid(sf.st_gid)->gr_name));
    display_size_file((int)sf.st_size, max_size_len);
    display_date(my_strdup(ctime(&sf.st_mtime)));
    my_putstr(data_file->d_name);
    my_printf("\n");
    return 0;
}

int handle_l_flag(struct dirent **tab_data_file, char *pathfile)
{
    int max_size_len = 0;
    struct stat sf;
    int blocks_size = 0;

    for (int j = 0; tab_data_file[j] != NULL; j++) {
        stat(handle_buff(pathfile, tab_data_file[j]->d_name), &sf);
        blocks_size += sf.st_blocks;
        if (my_len_int(sf.st_size) > max_size_len)
            max_size_len = my_len_int(sf.st_size);
    }
    my_printf("total %i\n", blocks_size / 2);
    for (int i = 0; tab_data_file[i] != NULL; i++) {
        display_l_flag(tab_data_file[i], max_size_len, pathfile);
    }
    return 0;
}
