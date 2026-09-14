##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for my_ls
##

SRC = 	main.c \
		parsing_functions.c \
		output_functions.c \
		flags.c \
		sudoers.c \
		useful_functions.c

NAME = my_sudo

LCNAME = unit_tests

CFLAGS = -Iinclude/. -Llib/my/ -lmy -lcrypt

LCFLAGS = --coverage -lcriterion

all:
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(SRC) $(CFLAGS)

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
		gcc -o $(NAME) $(SRC) $(CFLAGS) -g
		valgrind --leak-check=full ./my_ls

tests_run:
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(SRC) $(CFLAGS)
	sudo chown root:root $(NAME)
	sudo chmod u+s $(NAME)
