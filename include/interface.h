#ifndef INTERFACE_H  // Garde pour éviter les inclusions multiples
#define INTERFACE_H
// Inclusion du fichier board.h pour utiliser le type de données 'board' et 'tetromino'
#include "board.h"  
#include "tetromino.h"
/**
 * @brief Demande à la joueuse quelle action effectuer et renvoie un chiffre correspondant.
 * 
 * @return int - Code représentant l'action choisie :
 *                - 0 pour arrêter le jeu
 *                - 1 pour prendre un tétrmino dans le sac et le placer
 *                - 2 pour déplacer un tétrmino présent sur la grille
 */
int choose_action();    

/* Affiche toutes les informations du jeu (plateau, sac, score, etc.).
 
 @brief Affiche toutes les informations du jeu.

 @param board Le tableau contenant les informations du jeu à afficher.

 @return void (aucune valeur de retour)
 */
void display_board(board board);


/**
 * @brief Demande à la joueuse de sélectionner un tétrmino sur la grille.
 * 
 * @param board - Le tableau représentant la grille de jeu.
 * @return tetromino* - Pointeur vers le tétrmino sélectionné, ou NULL si aucun tétrmino n'est sélectionné.
 */
tetromino select_tetromino_on_grid(board board);

/**
 * @brief Demande à la joueuse de sélectionner un tétrmino du sac.
 * 
 * @param board - Le tableau représentant la grille de jeu.
 * @return tetromino* - Pointeur vers le tétrmino sélectionné, ou NULL si aucun tétrmino n'est sélectionné.
 */
tetromino select_tetromino_in_bag(board board);

/**
 * @brief Demande à la joueuse de sélectionner une ligne et une colonne où placer un tétrmino dans la grille.
 * 
 * @param board - Le tableau représentant la grille de jeu.
 * @param pr - Pointeur vers un entier qui sera mis à jour avec le numéro de ligne choisi.
 * @param pc - Pointeur vers un entier qui sera mis à jour avec le numéro de colonne choisi.
 *             Si aucune coordonnée n'est choisie, ces pointeurs devraient être NULL.
 */
void ask_place_tetromino(board board, int* pr, int* pc, tetromino tetromino);

/**
 * @brief Affiche un message de fin de jeu avec les informations associées.
 * 
 * @param board - Le tableau représentant la grille de jeu.
 */
void display_end_game(board board);

/**
 * @brief Affiche un message donné en entrée.
 * 
 * @param message - Le message à afficher.
 */
void display_message(char* message);


/* E.2 */


/* @requires : a valid tetromino
   @assigns : nothing
   @ensures : ask the player if he wants to turn the tetromino and deplace it
*/
void ask_turn_and_deplace_tetromino(board b, int *pr, int *pc, tetromino tr);

/* @requires : a valid tetromino
   @assigns : nothing
   @ensures : ask the player if he wants to turn the tetromino
*/
void ask_turn_tetromino(board b, int pr, int pc, tetromino tr);



#endif // INTERFACE_H
