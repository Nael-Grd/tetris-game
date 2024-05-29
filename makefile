CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
TEST_DIR = test

$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test1.o: $(TEST_DIR)/test1.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/test1: $(OBJ_DIR)/test1.o $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

	
