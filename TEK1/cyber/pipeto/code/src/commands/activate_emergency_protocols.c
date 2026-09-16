/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** activate_emergency_protocols
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pipeto.h"

void activate_emergency_protocols()
{
    char input[100];
    
    printf("Enter emergency password: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;

    if (strlen(input) == 0) {
        printf("No password entered, emergency protocols not activated.\n");
        return;
    }
    if (strcmp(input, "admin123") == 0) {
        printf("{Emergency protocols activated, you are now admin !}\n");
        IS_ADMIN = true;
    }
    return;
}
