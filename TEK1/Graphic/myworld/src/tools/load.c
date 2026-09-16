/*
** EPITECH PROJECT, 2025
** myworld
** File description:
** load
*/

#include "myworld.h"

int get_size(char *path)
{
    struct stat sb;

    lstat(path, &sb);
    return sb.st_size;
}

static void free_tab_line(char **tab_line)
{
    for (int i = 0; tab_line[i] != NULL; i++)
        free(tab_line[i]);
    free(tab_line);
}

static void add_line(int **tab, char *buff, int tab_len, int index)
{
    int *tmp_line = malloc(sizeof(int) * tab_len);
    char **tab_line = str_in_array(buff, ' ');

    if (!tmp_line) {
        free_tab_line(tab_line);
        free(tmp_line);
        return;
    }
    for (int i = 0; i < tab_len; i++)
        tmp_line[i] = atoi(tab_line[i]);
    tab[index] = tmp_line;
    free_tab_line(tab_line);
}

static int check_and_add(int **tab, int tab_len, char *buff_size, int index)
{
    int space_counter = 0;

    for (int i = 0; buff_size[i] != '\n'; i++)
        if (buff_size[i] == ' ')
            space_counter++;
    if (strlen(buff_size) != 0 && space_counter != tab_len - 1) {
        dprintf(2, "The file seems to be corrupted\n");
        return -1;
    }
    if (*buff_size != '\0')
        add_line(tab, buff_size, tab_len, index);
    return 0;
}

static int **interpret_file(FILE *file, char *buff, int **tab, int tab_len)
{
    char *buff_size = NULL;
    int result = 0;
    size_t line_len = 0;
    int index = 0;

    if (!tab)
        return NULL;
    fseek(file, 0, SEEK_SET);
    result = getline(&buff_size, &line_len, file);
    buff_size[strlen(buff_size) - 2] = 0;
    while (result != -1) {
        result = getline(&buff_size, &line_len, file);
        buff_size[strlen(buff_size) - 2] = 0;
        if (check_and_add(tab, tab_len, buff_size, index) == -1)
            return NULL;
        index++;
    }
    return tab;
}

static int check_file_header(FILE *file, char **first_line, size_t *line_size)
{
    fseek(file, 0, SEEK_SET);
    if (getline(first_line, line_size, file) == -1)
        return -1;
    if (strncmp("legend", *first_line, 6) != 0) {
        dprintf(2, "The file seems to be corrupted\n");
        fclose(file);
        return -1;
    }
    return 0;
}

static int **load_file(char *path, game_params_t *game_params)
{
    FILE *file = fopen(path, "r");
    int size = get_size(path);
    char buff[size + 1];
    int **tab = NULL;
    int tab_len = 0;
    char *first_line = NULL;
    size_t line_size = 0;

    fread(buff, 1, size, file);
    if (check_file_header(file, &first_line, &line_size) == -1)
        return NULL;
    tab_len = my_getnbr(first_line);
    game_params->world.size = tab_len;
    tab = malloc(sizeof(int *) * (tab_len));
    if (tab == NULL)
        return NULL;
    tab = interpret_file(file, buff, tab, tab_len);
    fclose(file);
    return tab;
}

int **load(game_params_t *game_params)
{
    int len = 0;
    char path[PATH_MAX_LEN];
    int **tab = NULL;

    file_explorer_load(path, PATH_MAX_LEN);
    if (*path == 0) {
        dprintf(1, "[OO] Canceled load\n");
        return NULL;
    }
    len = strlen(path);
    if (strlen(path) > 7 && strncmp(path + len - 7, ".legend", 7) == 0) {
        printf("Loaded file %s\n", path);
        tab = load_file(path, game_params);
        return tab;
    }
    printf("Cannot load file %s\n", path);
    return NULL;
}
