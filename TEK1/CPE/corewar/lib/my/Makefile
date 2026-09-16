##
## EPITECH PROJECT, 2024
## B-CPE-100-LIL-1-1-cpoolday10-theophile.riffe
## File description:
## lib makefile
##

SRC =	my_putchar.c					\
		my_str_to_word_array.c				\
		my_putstr.c						\
		my_put_nbr.c					\
		my_strlen.c						\
		my_getnbr.c						\
		my_puterr.c						\
		my_strcpy.c						\
		my_strncpy.c					\
		my_strcat.c						\
		my_strncat.c					\
		my_strcmp.c						\
		my_strncmp.c					\
		my_strstr.c						\
		split_string.c					\
		my_strdup.c						\
		my_str_isalpha.c				\
		my_str_isnum.c					\
		my_str_islower.c				\
		my_str_isupper.c				\
		my_str_isprintable.c			\
		my_strupcase.c					\
		my_strlowcase.c					\
		my_strcapitalize.c				\
		my_showstr.c					\
		my_showmem.c					\
		my_str_isnum.c					\
		my_swap.c						\
		my_sort_int_array.c				\
		my_compute_power_rec.c			\
		my_compute_square_root.c		\
		my_is_prime.c					\
		my_find_prime_sup.c				\
		my_revstr.c						\
		my_isneg.c						\
		my_show_word_array.c			\
		my_printf/my_printf.c			\
		my_printf/printf_putchar.c		\
		my_printf/printf_putnbr.c		\
		my_printf/printf_putstr.c		\
		my_printf/utilities.c			\
		my_printf/printf_putfloat.c		\
		my_printf/parse_flags.c			\
		my_printf/printf_putbase.c		\
		my_printf/utilities2.c			\
		my_printf/printf_scientific.c	\
		my_printf/utilities3.c			\
		my_printf/printf_n_spec.c		\
		my_printf/printf_g_spec.c		\
		my_printf/manage_spec.c		    \
		my_printf/put_buffer.c			\

OBJ = $(SRC:%.c=obj/%.o)

NAME = libmy.a

CC = gcc

CFLAGS = -Wall -Wextra -I../include

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@cp my.h ../../include/

obj/%.o: %.c
	@mkdir -p obj
	@mkdir -p obj/my_printf
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f $(OBJ)
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
