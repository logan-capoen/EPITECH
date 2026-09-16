/*
** EPITECH PROJECT, 2024
** B-CPE-100-LIL-1-1-cpoolday04-theophile.riffe
** File description:
** sort_int_array
*/

#include "my.h"

static int swap_elements(int *array, int size)
{
    int tmp = 0;
    int swapped = 0;

    for (int i = 0; i < size - 1; i++){
        if (array[i] > array[i + 1]){
            tmp = array[i];
            array[i] = array[i + 1];
    array[i + 1] = tmp;
            swapped = 1;
        }
    }
    return swapped;
}

void my_sort_int_array(int *array, int size)
{
    while (swap_elements(array, size))
        size--;
}
