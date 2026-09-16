/*
** EPITECH PROJECT, 2025
** help
** File description:
** handle the -h for robot factory
*/

/**
 * @file help.c
 * @brief Display the help menu if needed
 *
 * Check if -h flag was activated.
 * If it was, display the help menu.
 */

#include "../include/op.h"

/**
 * @brief Display the help menu
 */
static void display_help(void)
{
    my_printf("USAGE\n./asm file_name[.s]\nDESCRIPTION\n"
        "file_name file in assembly language to be converted"
        " into file_name.cor, an executable in\nthe "
        "Virtual Machine.\n");
}

/**
 * @brief Check if the -h flag was called
 *
 * @param argc The number of cli arguments
 * @param **argv The array of cli arguments
 * @return int 1 if help was displayed, else 0
 */
int check_help(int argc, char **argv)
{
    if (argc != 2 || my_strcmp(argv[1], "-h") != 0)
        return 0;
    display_help();
    return 1;
}
