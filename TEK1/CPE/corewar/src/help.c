/*
** EPITECH PROJECT, 2025
** help
** File description:
** handle the -h for corewar
*/

/*!
 * @file help.c
 * @brief Displays help information for the program.
 *
 * This file contains functions that display the usage instructions and help
 * messages when the -h flag is passed as a command line argument.
 */
#include "../include/op.h"

/*!
 * @brief Displays the help message.
 *
 * This function prints the usage instructions and descriptions to the
 * standard output.
 */
void display_help(void)
{
    my_printf("USAGE\n"
        "\t./corewar [-dump nbr_cycle] [[-n prog_number] "
        "[-a load_address] prog_name] ...\n"
        "DESCRIPTION\n"
        "\t-dump\n"
        "\tbr_cycle dumps the memory after the nbr_cycle execution "
        "(if the round isn't already over) with the following\n"
        "\tformat: 32 bytes/line in hexadecimal (A0BCDEFE1DD3...)\n"
        "\t-n\n"
        "\tprog_number sets the next program's number. "
        "By default, the first free number\n"
        "\tin the parameter order\n"
        "\t-a\n"
        "\tload_address sets the next program's loading address. "
        "When no address is specified,\n"
        "\toptimize the addresses so that the processes are as "
        "far away from each other as\n"
        "\tpossible. The addresses are MEM_SIZE modulo.\n");
}

/*!
 * @brief Checks if the help flag is provided.
 *
 * This function verifies the command line arguments to determine if the -h
 * flag has been passed. If so, it displays the help message.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of command line argument strings.
 *
 * @return 1 if the help flag is detected and help is displayed, 0 otherwise.
 */
int check_help(int argc, char **argv)
{
    if (argc != 2 || my_strcmp(argv[1], "-h") != 0)
        return 0;
    display_help();
    return 1;
}
