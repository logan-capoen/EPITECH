##
## EPITECH PROJECT, 2026
## myftp
## File description:
## Makefile
##
BIN = panoramix
C = epiclang
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
COV_DIR = coverage

SRC =   main.c \
		${SRC_DIR}/init.c \
		${SRC_DIR}/druid.c \
		${SRC_DIR}/villager.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS = -std=gnu17 -Wall -Wextra -I$(INC_DIR)

all: $(BIN)

$(BIN): $(OBJ)
	$(C) -o $(BIN) $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(C) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(COV_DIR)

fclean: clean
	rm -f $(BIN) $(TESTS_BIN)

re: fclean all
