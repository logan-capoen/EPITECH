##
## EPITECH PROJECT, 2026
## NanoTekSpice
## File description:
## Makefile
##
BIN = nanotekspice
CXX = clang++
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
TESTS_DIR = Crit_tests
TESTS_BIN = unit_tests
COV_DIR = coverage

SRC =   Main.cpp \
		$(SRC_DIR)/parsing/FileParser.cpp \
		$(SRC_DIR)/AComponent.cpp \
		$(SRC_DIR)/parsing/InputParser.cpp \
		$(SRC_DIR)/components/special/InputComponent.cpp \
		$(SRC_DIR)/components/special/OutputComponent.cpp \
		$(SRC_DIR)/components/special/FalseComponent.cpp \
		$(SRC_DIR)/components/special/TrueComponent.cpp \
		$(SRC_DIR)/components/special/ClockComponent.cpp \
		$(SRC_DIR)/components/elementary/AndComponent.cpp \
		$(SRC_DIR)/components/elementary/NotComponent.cpp \
		$(SRC_DIR)/components/elementary/OrComponent.cpp \
		$(SRC_DIR)/components/elementary/XorComponent.cpp \
		$(SRC_DIR)/components/gates/C4001.cpp \
		$(SRC_DIR)/components/gates/C4011.cpp \
		$(SRC_DIR)/components/gates/C4030.cpp \
		$(SRC_DIR)/components/gates/C4069.cpp \
		$(SRC_DIR)/components/gates/C4071.cpp \
		$(SRC_DIR)/components/gates/C4081.cpp \
		$(SRC_DIR)/components/gates/C4094.cpp \
		$(SRC_DIR)/components/advanced/C4514.cpp \
		$(SRC_DIR)/components/advanced/C4040.cpp \
		$(SRC_DIR)/components/advanced/C4017.cpp \
		$(SRC_DIR)/components/advanced/C4512.cpp \
		$(SRC_DIR)/components/advanced/C4008.cpp \
		$(SRC_DIR)/components/advanced/C4013.cpp \
		$(SRC_DIR)/components/advanced/C2716.cpp \
		$(SRC_DIR)/components/advanced/C4801.cpp \
		$(SRC_DIR)/components/advanced/Logger.cpp \
		$(SRC_DIR)/ComponentFactory.cpp \
		$(SRC_DIR)/Circuit.cpp

TESTS_SRC = $(TESTS_DIR)/test_ComponentFactory.cpp \
			$(TESTS_DIR)/test_Circuit.cpp \
			$(TESTS_DIR)/test_AComponent.cpp \
			$(TESTS_DIR)/test_ClockComponent.cpp \
			$(TESTS_DIR)/test_FalseComponent.cpp \
			$(TESTS_DIR)/test_TrueComponent.cpp \
			$(TESTS_DIR)/test_InputComponent.cpp \
			$(TESTS_DIR)/test_OutputComponent.cpp \
			$(TESTS_DIR)/test_AndComponent.cpp \
			$(TESTS_DIR)/test_NotComponent.cpp \
			$(TESTS_DIR)/test_OrComponent.cpp \
			$(TESTS_DIR)/test_C4001.cpp \
			$(TESTS_DIR)/test_C4011.cpp \
			$(TESTS_DIR)/test_C4030.cpp \
			$(TESTS_DIR)/test_C4069.cpp \
			$(TESTS_DIR)/test_C4071.cpp \
			$(TESTS_DIR)/test_C4081.cpp \
			$(TESTS_DIR)/test_C4094.cpp \
			$(TESTS_DIR)/test_C2076.cpp \
			$(TESTS_DIR)/test_C4008.cpp \
			$(TESTS_DIR)/test_C4013.cpp \
			$(TESTS_DIR)/test_C4017.cpp \
			$(TESTS_DIR)/test_C4040.cpp \
			$(TESTS_DIR)/test_C4512.cpp \
			$(TESTS_DIR)/test_C4514.cpp \
			$(TESTS_DIR)/test_C4801.cpp \
			$(TESTS_DIR)/test_Logger.cpp \
			$(TESTS_DIR)/test_FileParser.cpp \
			$(TESTS_DIR)/test_InputParser.cpp \

SRC_NO_MAIN = $(filter-out Main.cpp, $(SRC))

OBJ = $(SRC:%.cpp=$(OBJ_DIR)/%.o)
CXXFLAGS = -std=c++20 -Wall -Wextra -Werror -I$(INC_DIR)
TESTS_FLAGS = -std=c++20 -I$(INC_DIR) --coverage -lcriterion

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) -o $(BIN) $(OBJ)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(COV_DIR)

fclean: clean
	rm -f $(BIN) $(TESTS_BIN)

tests_run: fclean
	@mkdir -p $(COV_DIR)
	$(CXX) -o $(COV_DIR)/$(TESTS_BIN) $(SRC_NO_MAIN) $(TESTS_SRC) \
		$(TESTS_FLAGS)
	- cd $(COV_DIR) && ./$(TESTS_BIN)

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