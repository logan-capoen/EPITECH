##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for pong
##

SRC = 	pong.c

NAME = 101pong

LCNAME = unit_tests

LCFLAGS = --coverage -lcriterion

all:
	gcc -o $(NAME) $(SRC) -lm

clean:
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f $(LCNAME)
	rm -f $(NAME)

re:		fclean all

debug:
		gcc -o $(NAME) $(SRC) $(CFLAGS) -g
		valgrind --leak-check=full ./my_printf

unit_tests:
	gcc -o unit_tests tests/test_printf.c \
	-Iinclude/. -L. -lmy -lcriterion --coverage

tests_run:
	./$(LCNAME)
