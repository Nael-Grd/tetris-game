CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
EXPERIMENT_DIR=research_33/experiments

$(BIN_DIR)/tetris: $(OBJ_DIR)/board.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/interface.o $(OBJ_DIR)/main.o $(OBJ_DIR)/carte.o
	$(CC) $(CFLAGS)  $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/deepest_fit.o: $(EXPERIMENT_DIR)/deepest_fit.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/4n4n_S_Z.o: $(EXPERIMENT_DIR)/4n4n_S_Z.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/4n4n_S_Z: $(OBJ_DIR)/deepest_fit.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/board.o $(OBJ_DIR)/4n4n_S_Z.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/4n4n_J_L.o: $(EXPERIMENT_DIR)/4n4n_J_L.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/4n4n_J_L: $(OBJ_DIR)/deepest_fit.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/board.o $(OBJ_DIR)/4n4n_J_L.o
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/4n4n_T_O_I.o: $(EXPERIMENT_DIR)/4n4n_T_O_I.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/4n4n_T_O_I: $(OBJ_DIR)/deepest_fit.o $(OBJ_DIR)/tetromino.o $(OBJ_DIR)/board.o $(OBJ_DIR)/4n4n_T_O_I.o
	$(CC) $(CFLAGS) $^ -o $@

