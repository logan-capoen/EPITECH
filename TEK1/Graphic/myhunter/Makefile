##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for my_hunter
##

SRC = 	main.c \
		bird.c \
		game_params.c \
		handle_buttons.c \
		create_function.c \
		event.c \
		handle_audio.c \
		handle_buttons_game_over.c \
		handle_buttons_menu.c \
		handle_buttons_mod.c \
		handle_buttons_skin.c \
		handle_scene.c

NAME = my_hunter

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude/. -L. -lmy

LCFLAGS = --coverage -lcriterion

CSFMLFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C lib/my all
	gcc -o $(NAME) $(OBJ) $(CFLAGS) $(CSFMLFLAGS)

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
