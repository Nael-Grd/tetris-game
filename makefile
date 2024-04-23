CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
RESEARCH_DIR = research_33/experiments

$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS)  $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/deepest_fit.o:$(RESEARCH_DIR)/deepest_fit.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/4n4n.o:$(RESEARCH_DIR)/4n4n.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)4n4n: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/4n4n.o $(OBJ_DIR)/deepest_fit.o
	$(CC) $(CFLAGS)  $^ -o $@
