#include "../include/interface.h"
#include "../include/board.h"
#include <stdio.h>

// Fonction pour choisir l'action
int choose_action() {
    int action;
    printf("Voulez-vous arrêter le jeu ? Si oui, saisissez (0). Pour prendre un tétris dans le sac et le placer, saisissez (1). Si vous voulez déplacer un tétris présent sur la grille, saisissez (2) : \n");
    char input[100];
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &action);
    return action;
}

// Fonction pour afficher le plateau de jeu
void display_board(board my_board) {
    int** p = grille(my_board);
    int n_l = get_nbLignes(my_board);
    int n_C = nbColonnes(my_board);
    printf("Le nombre de lignes : %d \n", n_l);
    printf("Le nombre de colonnes : %d \n", n_C);
    
    // Affichage du plateau de jeu
    printf("Plateau de jeu :\n");
    for (int i = 0; i < n_l; i++) {
        for (int j = 0; j < n_C; j++) {
            printf("%4d ", p[i][j]);
        }
        printf("\n");
    }

    // Affichage du sac de tétriminos
    printf("\nSac de tétriminos :\n");
    tetromino *tetrominos = list_tetrominos_in_bag(my_board);
    for (int i = 0; i < 4; i++) {
        printf("Tétrimino %d : Type %d, Points %d\n", get_id(tetrominos[i]), get_type(tetrominos[i]), get_nb_points(tetrominos[i]));
    }
    printf("\n");

    // Affichage du score actuel
    printf("Score actuel : %d\n", get_score(my_board));
}

// Fonction pour sélectionner un tétris sur la grille
tetromino select_tetromino_on_grid(board my_board) {
    // Demande à l'utilisateur de sélectionner un tétris sur la grille
    printf("Veuillez choisir un tétris de la grille. Veuillez saisir un entier naturel pour le numéro de la colonne suivi par le numéro de ligne : \n");
    char input[100];
    int c = -1, r = -1;
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d %d", &c, &r);
    while (c < 0 || r < 0) {
        printf("Veuillez ressaisir des entiers positifs\n");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d %d", &c, &r);
    }
    tetromino tet = get_tetromino(my_board, r, c);
    return tet;
}

// Fonction pour sélectionner un tétris dans le sac
tetromino select_tetromino_in_bag(board board) {
    // Demande à l'utilisateur de sélectionner un tétris dans le sac
    printf("Veuillez choisir un tétris dans le sac. Veuillez saisir un entier naturel pour l'identifiant : \n");
    char input[100];
    int c = -1;
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d", &c);
    while (c < 0) {
        printf("Veuillez ressaisir un entier positif\n");
        fgets(input, sizeof(input), stdin);
        sscanf(input, "%d", &c);
    }

    // Retourne le tétris sélectionné, ou NULL si aucun tétris n'est sélectionné
    tetromino *tet;
    tet = list_tetrominos_in_bag(board);
    int taille = tailleSac(board);
    for (int i = 0; i < taille; i++) {
        if (get_id(tet[i]) == c)
            return tet[i];
    }
    return NULL;
}

// Fonction pour demander à l'utilisateur de placer un tétris sur la grille
void ask_place_tetromino(board board, int* r, int* c, tetromino tetromino) {
    // Demande à l'utilisateur de sélectionner une ligne et une colonne où placer le tétris dans la grille
    printf("Veuillez sélectionner une ligne et une colonne où placer le tétris dans la grille. Veuillez saisir un entier naturel pour le numéro de colonne suivi par le numéro de ligne : \n");

    // Les valeurs choisies sont stockées dans les pointeurs r et c
    *r = -1;
    *c = -1;
    char input[100];
    fgets(input, sizeof(input), stdin);
    sscanf(input, "%d %d", c, r);
    place_tetromino(board, *r, *c, tetromino);
}

// Fonction pour afficher la fin du jeu
void display_end_game(board board) {
    // Affiche un message de fin de jeu avec les informations associées
    printf("Fin du jeu\n");
    display_board(board);
}

// Fonction pour afficher un message
void display_message(char* message) {
    // Affiche le message donné en entrée
    printf("%s\n", message);
}
