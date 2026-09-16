##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile for secured
##

SRC = 	src/check_type.c \
		src/df_read_csv.c \
		src/df_write_csv.c \
		src/my_str_to_word_array.c \
		src/head.c \
		src/tail.c \
		src/shape.c \
		src/info.c \
		src/get_value.c \
		src/describe.c \
		src/apply.c \
		src/to_type.c \
		src/filtering.c \
		src/aggregation.c \
		src/sorting.c

NAME = libcuddle.a

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -lm -Iinclude

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f $(NAME)
	rm -f $(LCNAME)
	rm -f libmy.a

re:		fclean all
