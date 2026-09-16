##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC = 	my_putchar.c \
		my_strlen.c \
		my_put_nbr.c \
		my_putstr.c \
		my_getnbr.c \
        my_revstr.c \
		my_strcpy.c \
		my_strdup.c \
		my_compute_power_rec.c \
		my_strcat.c \
		tools_flags.c \
		my_strcmp.c \
		my_strlowcase.c \
		my_strncmp.c	\
		my_str_to_word_array.c \

OBJ = $(SRC:.c=.o)

NAME = libmy.a

CFLAGS	+=	-g

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp libmy.a ../
	cp libmy.a ../../

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ../libmy.a

re:		fclean all
