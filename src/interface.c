#include "../include/interface.h"
#include "../include/board.h"
#include <stdio.h>

// Obliger de redefinir la structure BoardStruct ici pour pouvoir acceder aux information de celle-ci
struct BoardStruct
{
    int nbLignes;    // Nombre de lignes du plateau
    int nbColonnes;  // Nombre de colonnes du plateau
    int tailleSac;   // Taille du sac de tétrominos
    tetromino *sac;  // Sac de tétrominos
    int **grille;    // Grille du plateau de jeu
    int scoreActuel; // Score actuel
};



//la fonction choose_action
int choose_action() {
    int action;
    printf("Voulez-vous arrêter le jeu ? Si oui, saisissez (0). Si vous voulez placer un tétrmino, saisissez (1). Si vous voulez placer un tétrmino, saisissez (2) ? \n");
    scanf("%d", &action);
    return action;
}
//la fonction display_board
void display_board(board my_board) {
    // Affichage du plateau de jeu
    printf("Plateau de jeu :\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            printf("%4d ", my_board->grille[i][j]);
        }
        printf("\n");
    }

    // Affichage du sac de tétriminos
    printf("\nSac de tétriminos :\n");
    tetromino *tetrominos = list_tetrominos_in_bag(my_board);
    for (int i = 0; i < 5; i++) {
        printf("Tétrimino %d : Type %d, Points %d\n", i+1, get_type(tetrominos[i]), get_nb_points(tetrominos[i]));
    }
    printf("\n");

    // Affichage du score actuel
    printf("\nScore actuel : %d\n", get_score(my_board));
}

//la fonction  select_tetromino_on_grid
tetromino select_tetromino_on_grid(board my_board) {
    // Demande à la joueuse de sélectionner un tétromino sur la grille
    printf("Veuillez choisir un tétromino de la grille\n");
    printf("Veuillez saisir un entier naturel\n");
    int c = -1;
    int r = -1;
    scanf("%d", &c);
    while (c < 0) {
        printf("Veuillez ressaisir un entier positif\n");
        scanf("%d", &c);
    }
    scanf("%d", &r);
    while (r < 0) {
        printf("Veuillez ressaisir un entier positif\n");
        scanf("%d", &r);
    }
    tetromino tet = get_tetromino(my_board, r, c);
    return tet;
}
//la fonction select_tetromino_in_bag
tetromino select_tetromino_in_bag(board board) {
    // Demande à la joueuse de sélectionner un tétrmino dans le sac
    printf("Veuillez choisir un tétrmino dans le sac\n");
    printf("Veuillez saisir un entier naturel\n");
    int c = -1;
    scanf("%d", &c);
    while (c < 0) {
        printf("Veuillez ressaisir un entier positif\n");
        scanf("%d", &c);
    }

    // Retourne le tétrmino sélectionné, ou NULL si aucun tétrmino n'est sélectionné
    tetromino *tet;
    tet = list_tetrominos_in_bag(board);
    for (int i = 0; i < 5; i++) {
        if (get_id(tet[i]) == c)
            return tet[i];
    }
    return NULL;
}
//la fonction ask_place_tetromino
void ask_place_tetromino(board board, int* r, int* c, tetromino tetromino) {
    // Demande à la joueuse de sélectionner une ligne et une colonne où placer le tétrmino dans la grille
    printf("Veuillez sélectionner une ligne et une colonne où placer le tétrmino dans la grille\n");

    // Les valeurs choisies sont stockées dans les pointeurs r et c
    printf("Veuillez choisir une valeur de colonne [entier] : \n");
    scanf("%d", c);
    while (*c == -1) {
        printf("Veuillez ressaisir un entier naturel\n");
        scanf("%d", c);
    }

    printf("Veuillez choisir une valeur de ligne [entier] : \n");
    scanf("%d", r);
    while (*r == -1) {
        printf("Veuillez ressaisir un entier naturel\n");
        scanf("%d", r);
    }

    int p = place_tetromino(board, *r, *c, tetromino);
    
}
// la fonction display_end_game 
void display_end_game(board board) {
    // Affiche un message de fin de jeu avec les informations associées
    printf("Fin du jeu\n");
}
// la fonction display_message
void display_message(char* message) {
    // Affiche le message donné en entrée
    printf("%s\n", message);
}
