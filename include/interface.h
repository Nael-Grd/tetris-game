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


/**
 * @brief Demande à l'utilisateur de spécifier une rotation pour le tétrimino.
 *
 * Cette fonction affiche les options de rotation disponibles et invite l'utilisateur
 * à entrer un choix. Ensuite, elle applique la rotation choisie au tétrimino.
 *
 * @param tetromino Le tétrimino à faire pivoter.
 */
void ask_rotate_tetromino(tetromino tetromino);







/* DEBUT TACHE E4*/
/**
 * @file cartes_operations.h
 * @brief Functions for managing special cards on the board.
 */

/**
 * @brief Displays information about a specific card.
 * 
 * @param cte The card to display.
 */
void show_card(carte cte);

/**
 * @brief Executes the necessary action based on the selected card.
 * 
 * @param b A pointer to the board structure.
 * @param c The index of the card to use.
 */
void to_need_to_use_card(board* b, int c);

/**
 * @brief Asks the user if they want to use a special card and performs the action if chosen.
 * 
 * @param b A pointer to the board structure.
 */
void ask_use_card(board* b);

/*FIN de TACHE:E4 */


#endif // INTERFACE_H
