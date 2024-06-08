CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
TEST_DIR = test

<<<<<<< HEAD
$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@
=======
$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o $(OBJ_DIR)/carte.o
	$(CC) $(CFLAGS)  $^ -o $@
>>>>>>> 63faeef75d99873448f1cdd402e62befa0e83091

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR)/test1.o: $(TEST_DIR)/test1.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)

$(BIN_DIR)/test1: $(OBJ_DIR)/test1.o $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/carte.o
	$(CC) $(CFLAGS) $^ -o $@ -lcunit

	
