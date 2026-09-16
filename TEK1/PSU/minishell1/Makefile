##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for minishell1
##

SRC = 	main.c \
		handle_env.c \
		fork.c \
		free_functions.c \
		cd_function.c \
		tool_functions.c

NAME = mysh

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude -L. -lmy

LCFLAGS = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(OBJ) $(CFLAGS) -g

libmy.a:
	$(MAKE) -C lib/my

clean:
	$(MAKE) -C lib/my clean
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	$(MAKE) -C lib/my fclean
	rm -f $(NAME)
	rm -f $(LCNAME)
	rm -f libmy.a

re:		fclean all

debug:
	$(MAKE) -C lib/my all
	gcc -Wall -Wextra -Werror -g -o $(NAME) $(OBJ) $(CFLAGS)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./mysh
