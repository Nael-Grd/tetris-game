#ifndef __DEEPEST_FIT__
#define __DEEPEST_FIT__
#include "../../include/board.h"

/* @requires : board b, tetromino t, L the row f all the lower empty places
   @asssigns : L
   @ensures :  returning an array of all the lower empty places represented by t's id*/
int** plus_bas(tetromino t, board b, int* L);


/* @requires : board b, tetromino t,C and L the column and the row f all the lower empty places and taille its width
   @asssigns : C, L, and taille
   @ensures :  returning an array of all the lower empty places represented by t's id*/
int** plus_petit(tetromino t, board b, int* C, int* L, int* taille);

/* @requires : board b, C and L the column and the row f all the lower empty places and taille its width
   @asssigns : C, L, and taille
   @ensures :  returning the index of the tetromino that minimizes the highest occupiable spot*/
int piece_min(board b, int* C, int* L, int* taille);

/* @requires : board b
   @asssigns : b
   @ensures :  placing the tetromino according to the Deepest_Fit method*/
void deepest_fit(board b);



#endif