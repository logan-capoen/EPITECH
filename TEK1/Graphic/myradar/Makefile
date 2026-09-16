##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for my_radar
##

SRC = 	main.c \
		create_function.c \
		handle_planes.c \
		detection.c

NAME = my_radar

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude/. -L. -lmy -lm

LCFLAGS = --coverage -lcriterion

CSFMLFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	gcc -g -o $(NAME) $(OBJ) $(CFLAGS) $(CSFMLFLAGS)

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
