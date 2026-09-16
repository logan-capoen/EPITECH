/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** globbings
*/

#ifndef GLOBBINGS_H_
    #define GLOBBINGS_H_
    #include <glob.h>
    #include "meowsh.h"
    #include <sys/stat.h>
    #define MAX_GLOBS 2048

int is_gobbling(char *str);
char *get_globbings(char *find);
char *create_concat_array(char **pathv);

#endif /* !GLOBBINGS_H_ */
