# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
TEST_DIR = test

# Source files
SRCS = $(SRC_DIR)/board.c $(SRC_DIR)/tetromino.c $(SRC_DIR)/interface.c $(SRC_DIR)/main.c $(SRC_DIR)/carte.c
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

TEST_SRCS = $(TEST_DIR)/test1.c
TEST_OBJS = $(OBJ_DIR)/test1.o

# Targets
all: $(BIN_DIR)/tetris $(BIN_DIR)/test1

$(BIN_DIR)/tetris: $(OBJS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN_DIR)/test1: $(TEST_OBJS) $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/carte.o | $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/test1.o: $(TEST_DIR)/test1.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: all clean

