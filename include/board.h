#ifndef __board_h__
#define __board_h__
#include "tetromino.h"
#include "carte.h"
#include <stdbool.h>
typedef struct BoardStruct *board;

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
 * @return 1 si le tétraaddminos a été placé avec succès, 0 sinon.
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

/**
 * Signature get_nbLignes
 * @param b Le plateau de jeu.
 * @return Nombre de lignes du plateau.
 */
int get_nbLignes(board b);

/**
 * Signature nbColonnes
 * @param b Le plateau de jeu.
 * @return Nombre de colonnes du plateau.
 */
int nbColonnes(board b);

/**
 * Signature tailleSac
 * @param b Le plateau de jeu.
 * @return Taille du sac de tétrominos.
 */
int tailleSac(board b);

/**
 * Signature sac
 * @param b Le plateau de jeu.
 * @return Sac de tétrominos.
 */
tetromino *sac(board b);

/**
 * Signature grille
 * @param b Le plateau de jeu.
 * @return Grille du plateau de jeu.
 */
int **grille(board b);

/**
 * Tâche E3
 * Fonction 'reserve_tetromino'
 * @param b le plateau.
 * @param t le tetromino concerné.
 * @return 1 si réservé, 0 sinon.
*/

void  reserve_tetromino(board b,tetromino t);

/**
 * Tâche E3
 * Fonction 'remove_tetromino'
 * @param b le plateau.
 * @return le tetromino réservé.
*/

void  remove_tetromino_from_reserve(board b);

/**
 * Tâche E3
 * Fonction 'list_reserve'
 * @param b le plateau.
 * @return la réserve.
*/

tetromino* list_reserve(board b);




/*TACHE:E4 done by ALI DAOUDI */

typedef void effect; // Assuming effect is a function pointer type

// Function prototypes
/**
 * @brief Checks if the reserve is full.
 *
 * @param b The board structure.
 * @return true if the reserve is full, false otherwise.
 */
int reserve_is_full(board b);

/**
 * @brief Displays the contents of the reserve.
 *
 * @param b The board structure.
 */
void show_reserve(board b);

/**
 * @brief Adds an amount to the board's score.
 *
 * @param b A pointer to the board structure.
 * @param amount The amount to add to the score.
 */
void add_to_score(board b, int amount);

/**
 * @brief Gets the size of the bag.
 *
 * @param b The board structure.
 * @return The size of the bag.
 */
int get_size_bag(board b);

/**
 * @brief Gets the size of the reserve.
 *
 * @param b The board structure.
 * @return The size of the reserve.
 */
int get_size_reserve(board b);

/**
 * @brief Checks if a tetromino is present on the board.
 *
 * @param b The board structure.
 * @param t The tetromino to check.
 * @return true if the tetromino is present, false otherwise.
 */
bool is_card(board b, tetromino t);

/**
 * @brief Gets a card associated with a tetromino.
 *
 * @param b The board structure.
 * @param t The tetromino.
 * @return The card if the tetromino is a card, otherwise NULL.
 */
carte get_card(board b, tetromino t);

/**
 * @brief Removes a card from the board's list of cards.
 *
 * @param b A pointer to the board structure.
 * @param num The number of the card to remove.
 */
void remove_card(board b, int num);

/**
 * @brief Adds a card to the board's list of cards.
 *
 * @param b A pointer to the board structure.
 * @param cte The card to add.
 */
void add_card(board b, carte cte);

/**
 * @brief Applies the effect of the Thuy Vo card.
 *
 * @param b A pointer to the board structure.
 */
effect Thuy_Vo(board b);

/**
 * @brief Applies the effect of the David Roussel card.
 *
 * @param b A pointer to the board structure.
 */
effect David_Roussel(board b);

/**
 * @brief Applies the effect of the Abass Sagna card.
 *
 * @param b A pointer to the board structure.
 */
effect Abass_Sagna(board b);

/**
 * @brief Applies the effect of the Renaud Rioboo card.
 *
 * @param b A pointer to the board structure.
 * @param tr The tetromino to remove.
 */
effect  Renaud_Rioboo(board b, tetromino tr);

/**
 * @brief Applies the effect of the Laurence Bourard card.
 *
 * @param b A pointer to the board structure.
 * @param t The tetromino to exchange with the reserve.
 */
effect Laurence_Bourard(board b, tetromino t);

/**
 * @brief Applies the effect of the Massinissa Merabet card.
 *
 * @param b A pointer to the board structure.
 */
effect Massinissa_Merabet(board b);

/**
 * @brief Applies the effect of the Anne Laure Ligozat card.
 *
 * @param b A pointer to the board structure.
 * @param tr The tetromino to remove.
 */
effect Anne_Laure_Ligozat(board b, tetromino tr);

/**
 * @brief Applies the effect of the Christophe Mouilleron card.
 *
 * @param b A pointer to the board structure.
 */
effect Christophe_Mouilleron(board b);

/**
 * @brief Applies the effect of the Cyril Benezet card.
 *
 * @param b A pointer to the board structure.
 * @param n The index of the tetromino to change.
 */
effect Cyril_Benezet(board b, int n);

/**
 * @brief Applies the effect of the Dimitri Watel card.
 *
 * @param b A pointer to the board structure.
 */
effect Dimitri_Watel(board b);

/**
 * @brief Applies the effect of the Marie Szafranski card.
 *
 * @param b A pointer to the board structure.
 */
effect Marie_Szafranski(board b);


bool reserve_is_empty(board b);


tetromino get_tetromino_from_reserve(board b);

/*TACHE:E4 done by ALI DAOUDI*/
#endif
