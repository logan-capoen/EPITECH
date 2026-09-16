##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for my_hunter
##


SRC = 	src/main.c 							        \
		src/buttons/create_buttons.c 		    	\
		src/tools/create_function.c 		    	\
		src/event/event.c 					        \
		src/buttons/handle_buttons_menu.c 			\
		src/event/handle_scene.c 			      	\
		src/world.c							        \
		src/tools/utilities.c				        \
		src/tools/save.c                    		\
    	src/event/handle_scene_world.c				\
		src/tools/load.c							\
		src/tools/explorer.c						\
		src/buttons/click_on_buttons_world.c		\
		src/terraform.c								\
		src/browse_map.c							\
		src/destroy.c

NAME = my_world

OBJ = $(SRC:.c=.o)

LCNAME = unit_tests

CFLAGS = -Iinclude/. -L. -lmy

LCFLAGS = --coverage -lcriterion

CSFMLFLAGS = -lcsfml-graphics -lcsfml-system -lcsfml-window -lcsfml-audio -lm

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
