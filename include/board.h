#ifndef __board_h__
#define __board_h__
#include "tetromino.h"

typedef void *board;

/**
 * Signature create_board
 * @param n Le nombre de lignes de la grille.
 * @param m Le nombre de colonnes de la grille.
 * @param k La taille du sac.
 * @return Un board initialisé avec une grille vide de n lignes et m colonnes, et un sac de taille k.
 */
board create_board(int n, int m, int k);

/**
 * Signature free_board
 * @param b Le board à libérer.
 */
void free_board(board b);

/**
 * Signature list_tetrominos_in_bag
 * @param b Le board dont on veut la liste des tétraminos dans le sac.
 * @return Un tableau de tétraminos présents dans le sac.
 */
tetromino *list_tetrominos_in_bag(board b);

/**
 * Signature add_tetromino_to_bag
 * @param b Le board auquel ajouter le tétraminos dans le sac.
 * @param t Le tétraminos à ajouter.
 */
void add_tetromino_to_bag(board b, tetromino t);

/**
 * Signature remove_tetromino_from_bag
 * @param b Le board duquel retirer le tétraminos du sac.
 * @param t Le tétraminos à retirer.
 */
void remove_tetromino_from_bag(board b, tetromino t);

/**
 * Signature check_place_tetromino
 * @param b Le board sur lequel vérifier la possibilité de placer le tétraminos.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @param t Le tétraminos à placer.
 * @return 1 si le tétraminos peut être placé, 0 sinon.
 */
int check_place_tetromino(board b, int r, int c, tetromino t);

/**
 * Signature place_tetromino
 * @param b Le board sur lequel placer le tétraminos.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @param t Le tétraminos à placer.
 * @return 1 si le tétraminos a été placé avec succès, 0 sinon.
 */
int place_tetromino(board b, int r, int c, tetromino t);

/**
 * Signature remove_tetromino
 * @param b Le board duquel retirer le tétraminos.
 * @param r Pointeur vers la ligne de référence.
 * @param c Pointeur vers la colonne de référence.
 * @param t Le tétraminos à retirer.
 */
void remove_tetromino(board b, int *r, int *c, tetromino t);

/**
 * Signature get_tetromino
 * @param b Le board sur lequel chercher le tétraminos.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @return Le tétraminos trouvé ou NULL s'il n'y en a pas.
 */
tetromino get_tetromino(board b, int r, int c);

/**
 * Signature get_score
 * @param b Le board pour lequel obtenir le score.
 * @return Le score courant.
 */
int get_score(board b);

#endif
