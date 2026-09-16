/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday07-theophile.riffe
** File description:
** putchar
*/

#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
