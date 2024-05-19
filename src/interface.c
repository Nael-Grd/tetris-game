#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/interface.h"

const char* tetromino_types[7] = {"I", "L", "Y", "A", "S", "E", "Z"}; /**< Tableau des types de tétriminos pour afficher les lettres au lieu des chiffres. */

/**
 * @brief Choisir l'action à effectuer par le joueur.
 * 
 * @param b Le plateau de jeu.
 * @return L'action choisie par le joueur.
 */
int choose_action(board b) {
    // À chaque tour, le joueur peut toujours décider d'arrêter le jeu ou de prendre un tétrimino du sac pour le placer dans la grille.
    printf("Choisissez votre prochaine action: \n 0 : Mettre fin à la partie.\n 1 : Prendre un tétrimino du sac pour le placer. \n");

    if (tetromino_in_board(b)) {
        // Si le plateau n'est pas vide, le joueur doit avoir la possibilité de déplacer un tétrimino.
        printf("2 : Déplacer un tétrimino présent sur la grille. \n");
        printf("3 : Tourner un tétrimino présent sur la grille. \n"); // Ajout de Wissem Flitti (Tâche E.2).
        if (reserve_is_empty(b)) {
            // Si en plus de cela le réserve est vide, le joueur doit avoir la possibilité de placer un tétrimino du plateau vers la réserve.
            printf("4 : Placer un tétrimino de la grille dans la réserve. \n");
        } else if (!reserve_is_empty(b)) {
            // Si en plus de cela, le réserve est non vide, alors le joueur doit avoir la possibilité de placer le tétrimino de la réserve vers le plateau.
            printf("4 : Placer un tétrimino de la réserve dans la grille. \n");
        }
    } else if (!tetromino_in_board(b)) {
        if (!reserve_is_empty(b)) {
            // Si le plateau est vide et que le réserve est non vide, alors le joueur doit avoir la possibilité de mettre le tétrimino de la réserve dans la grille.
            printf("2 : Placer un tétrimino de la réserve dans la grille. \n");
        }
    }

    int choice;
    printf("\nEntrez votre choix : ");
    scanf("%d", &choice);

    if (tetromino_in_board(b)) {
        while (!(choice == 0 || choice == 1 || choice == 2 || choice == 3 || choice == 4)) {
            printf("Veuillez entrer un entier valide: 0, 1, 2, 3 ou 4.\n");
            scanf("%d", &choice);
        }
    } else if (!tetromino_in_board(b)) {
        while (!(choice == 0 || choice == 1 || choice == 2)) {
            printf("Veuillez entrer un entier valide: 0, 1 ou 2.\n");
            scanf("%d", &choice);
        }
    }

    return choice;
}

/**
 * @brief Demande au joueur où placer le tétrimino.
 * 
 * @param b Le plateau de jeu.
 * @param row La ligne choisie.
 * @param col La colonne choisie.
 * @param t Le tétrimino à placer.
 * @param state L'état actuel du jeu.
 */
void ask_place_tetromino(board b, int *row, int *col, tetromino t, int state) {
    printf("Entrez la ligne et la colonne où vous voulez placer le tétrimino (format: ligne colonne): ");
    scanf("%d %d", row, col);

    while (!is_valid_placement(b, *row, *col, t)) {
        printf("Placement invalide. Essayez de nouveau (format: ligne colonne): ");
        scanf("%d %d", row, col);
    }
}

/**
 * @brief Demande au joueur s'il souhaite tourner le tétrimino.
 * 
 * @param t Le tétrimino à tourner.
 */
void ask_turn_tetromino(tetromino t) {
    int choice;
    printf("Voulez-vous tourner le tétrimino ? (0: Non, 1: Oui) : ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Entrez le nombre de rotations (1, 2 ou 3) : ");
        int rotations;
        scanf("%d", &rotations);
        for (int i = 0; i < rotations; i++) {
            rotate_tetromino(t);
        }
    }
}

/**
 * @brief Sélectionne un tétrimino présent sur la grille.
 * 
 * @param b Le plateau de jeu.
 * @return Le tétrimino sélectionné.
 */
tetromino select_tetromino_on_grid(board b) {
    printf("Sélectionnez le tétrimino sur la grille (entrez les coordonnées de la cellule occupée par le tétrimino, format: ligne colonne): ");
    int row, col;
    scanf("%d %d", &row, &col);

    while (!is_cell_occupied(b, row, col)) {
        printf("Cellule vide. Essayez de nouveau (format: ligne colonne): ");
        scanf("%d %d", &row, &col);
    }

    return get_tetromino_at(b, row, col);
}

/**
 * @brief Demande au joueur s'il souhaite utiliser une carte spéciale.
 * 
 * @param b Le plateau de jeu.
 */
void ask_use_card(board *b) {
    carte* list_cards = get_list_card(*b);
    printf("\nVoulez-vous utiliser une carte spéciale ?\n");
    printf("0 : Non / 1 : Oui\n");
    int choice;
    printf("\nEntrez votre choix : ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\n<< Liste des cartes disponibles >>\n\n");
        for (int i = 0; i < 8; i++) {
            if (list_cards[i] != NULL) {
                printf("Carte spéciale n° : %d", i);
                show_card(list_cards[i]);
            }
        }
        printf("Entrez le numéro de carte que vous voulez utiliser :\n");
        int card_num;
        scanf("%d", &card_num);
        use_card(b, card_num);
    } else {
        printf("\nVous n'avez pas utilisé de carte spéciale.\n");
    }
}
