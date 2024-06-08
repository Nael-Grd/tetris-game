# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
TEST_DIR = test


all: $(BIN_DIR)/tetris $(BIN_DIR)/test1

$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o $(OBJ_DIR)/carte.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test1: $(OBJ_DIR)/test1.o $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/carte.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lcunit


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test1.o: $(TEST_DIR)/test1.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

