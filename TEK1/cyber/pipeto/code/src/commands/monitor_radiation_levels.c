/*
** EPITECH PROJECT, 2024
** Pipeto
** File description:
** monitor_radiation_levels
*/

#include <stdio.h>
#include <string.h>
void secret_function ()
	{
		printf (
				"{The stone isn't in the pocket anymore ...}\n");
	}
void monitor_radiation_levels ()
	{
		char    buffer[10];
		void (* function_ptr) () = NULL;
		printf ("Enter radiation levels: ");
		gets (buffer);
		printf ("Radiation Levels: %s\n" ,buffer);
		printf("ADDRESS %p\n", secret_function);
		if (function_ptr)
			{
				function_ptr();
			} else
			{
				printf ("Function Pointer: %p\n"
						,( void * ) function_ptr);
			}
	}
