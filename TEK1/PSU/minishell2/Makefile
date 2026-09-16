##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for minishell1
##

SRC = 	src/main.c \
		src/handle_env.c \
		src/fork.c \
		src/free_functions.c \
		src/cd_function.c \
		src/tool_functions.c \
		src/handle_input.c \
		src/handle_param.c

NAME = mysh

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude -L. -lmy -Wall -Wextra

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
	valgrind --leak-check=full --show-leak-kinds=all ./mysh

tests_run: clean
	gcc -o unit_tests $(TESTSRC) \
		--coverage -lcriterion $(CFLAGS)
	
	./unit_tests

	gcovr --exclude inclue/
	gcovr --exclude inclue/ --branches
