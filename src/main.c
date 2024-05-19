#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/interface.h"
#include <stdlib.h>
#include <time.h>

/**
 * @brief Initialise le jeu avec un plateau et un sac de tétriminos.
 * 
 * @param n Le nombre de lignes et de colonnes du plateau.
 * @param k Le nombre de tétriminos dans le sac.
 * @return Le plateau de jeu initialisé.
 */
board init_jeu(int n, int k) {
    board b = create_board(n, n, k);
    for (int i = 0; i < 4; i++) {
        tetromino t_init = create_random_tetromino();
        add_tetromino_to_bag(&b, t_init);
    }
    return b;
}

/**
 * @brief Gère le placement d'un tétrimino sur le plateau.
 * 
 * @param b L'adresse du plateau.
 * @param t L'adresse du tétrimino.
 * @param etat L'état actuel du jeu.
 */
void gestion_placement(board b, tetromino t, int etat) {
    int row;
    int col;
    ask_turn_tetromino(t);
    ask_place_tetromino(b, &row, &col, t, etat);
    place_tetromino(&b, row, col, t);
}

/**
 * @brief Gère le sac après un mouvement de tétrimino sur le plateau.
 * 
 * @param b L'adresse du plateau.
 * @param t L'adresse du tétrimino.
 */
void gestion_du_sac_apres_mouvement(board b, tetromino t) {
    remove_tetromino_from_bag(&b, t);
    tetromino new_tetromino = create_random_tetromino();
    add_tetromino_to_bag(&b, new_tetromino);
}

/**
 * @brief Fonction principale qui lance le jeu.
 * 
 * @return 0 si le jeu se termine correctement.
 */
int main() {
    srand(time(NULL));

    int taille_plateau;
    int taille_sac;
    printf("Entrez la taille du plateau (nxn): ");
    scanf("%d", &taille_plateau);
    printf("Entrez la taille du sac de tétriminos: ");
    scanf("%d", &taille_sac);

    board b = init_jeu(taille_plateau, taille_sac);
    display_board(b);

    int etat_action;
    while (1) {
        printf("Choisissez une action (1: Placer un nouveau tétrimino, 2: Déplacer un tétrimino, 3: Tourner un tétrimino, 4: Placer un tétrimino dans la réserve): ");
        scanf("%d", &etat_action);

        if (etat_action == 1) {
            if (!bag_is_empty(b)) {
                tetromino t = get_tetromino_from_bag(b);
                gestion_placement(b, t, etat_action);
                display_board(b);
            } else {
                printf("Le sac est vide.\n");
            }
        } else if (etat_action == 2 && tetromino_in_board(b)) {
            tetromino t = select_tetromino_on_grid(b);
            int old_row;
            int old_col;
            remove_tetromino(&b, &old_row, &old_col, t);
            gestion_placement(b, t, etat_action);
            if (!tetromino_in_board(b)) {
                place_tetromino(&b, old_row, old_col, t);
                display_board(b);
            }
        } else if (etat_action == 3 && tetromino_in_board(b)) {
            tetromino t = select_tetromino_on_grid(b);
            int row;
            int col;
            remove_tetromino(&b, &row, &col, t);
            ask_turn_tetromino(t);
            place_tetromino(&b, row, col, t);
            display_board(b);
        } else if (etat_action == 4 && reserve_is_empty(b)) {
            tetromino t = select_tetromino_on_grid(b);
            gestion_placement_grille_vers_reserve(b, t);
        } else if ((etat_action == 4 && !reserve_is_empty(b)) || (etat_action == 2 && !tetromino_in_board(b))) {
            tetromino t = get_tetromino_from_reserve(b);
            gestion_placement_reserve_vers_grille(b, t, etat_action);
        } else {
            printf("Action invalide ou impossible.\n");
        }
    }

    free_board(&b);
    return 0;
}
