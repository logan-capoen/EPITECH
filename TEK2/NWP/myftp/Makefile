##
## EPITECH PROJECT, 2026
## myftp
## File description:
## Makefile
##
BIN = myftp
C = epiclang
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TESTS_DIR = Crit_tests
TESTS_BIN = unit_tests
COV_DIR = coverage

SRC =   main.c \
		$(SRC_DIR)/auth.c \
        $(SRC_DIR)/command_handler.c \
        $(SRC_DIR)/simple_commands.c \
        $(SRC_DIR)/file_transfer.c \
        $(SRC_DIR)/list.c \
        $(SRC_DIR)/navigation.c \
        $(SRC_DIR)/transfer_mode.c \
        $(SRC_DIR)/utils.c \
        $(SRC_DIR)/wrap.c \
        $(SRC_DIR)/wrap2.c \


TESTS_SRC = $(TESTS_DIR)/tests.c

SRC_NO_MAIN = $(filter-out main.c, $(SRC))

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS = -std=gnu17 -Wall -Wextra -I$(INC_DIR)
TESTS_FLAGS = -std=c++20 -I$(INC_DIR) --coverage -lcriterion

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

tests_run: fclean
	@mkdir -p $(COV_DIR)
	$(C) -o $(COV_DIR)/$(TESTS_BIN) $(SRC_NO_MAIN) $(TESTS_SRC) \
		$(TESTS_FLAGS)
	cd $(COV_DIR) && ./$(TESTS_BIN)

coverage: tests_run
	@mkdir -p $(COV_DIR)/report
	gcovr \
		--gcov-executable "llvm-cov gcov" \
		--exclude $(TESTS_DIR)/ \
		--exclude $(INC_DIR)/ \
		--object-directory $(COV_DIR) \
		--output $(COV_DIR)/coverage.txt
	gcovr \
		--gcov-executable "llvm-cov gcov" \
		--exclude $(TESTS_DIR)/ \
		--exclude $(INC_DIR)/ \
		--object-directory $(COV_DIR) \
		--branches \
		--output $(COV_DIR)/coverage_branches.txt
	gcovr \
		--gcov-executable "llvm-cov gcov" \
		--exclude $(TESTS_DIR)/ \
		--exclude $(INC_DIR)/ \
		--object-directory $(COV_DIR) \
		--html --html-details \
		-o $(COV_DIR)/report/coverage.html
	cat $(COV_DIR)/coverage.txt
	cat $(COV_DIR)/coverage_branches.txt
	xdg-open $(COV_DIR)/report/coverage.html

re: fclean all
