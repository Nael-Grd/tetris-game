CC = gcc -Wall -Wextra -std=c99

all: tetris

tetris: board.o tetromino.o interface.o main.o
	$(CC) $^ -o $@

%.o: %.c %.h
	$(CC) -c $< -o $@
