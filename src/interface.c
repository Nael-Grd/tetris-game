#include "../include/interface.h"
#include "../include/board.h"
#include <stdio.h>

//la fonction choose_action
int choose_action() {
    int action;
    printf("Voulez-vous arrêter le jeu ? Si oui, saisissez (0).  prendre un tétromino dans le sac et le placer, auquel cas , saisissez (1). Si vous voulez déplacer un tétromino présent sur la grille, saisissez (2) ? \n");
    scanf("%d", &action);
    return action;
}
//la fonction display_board
void display_board(board my_board) {
    int** p=grille(my_board);
    int n_l=get_nbLignes(my_board);
    int n_C=nbColonnes(my_board);
    printf("le nombre de lignes %d \n" , n_l);
    printf("le nombre de colone %d \n", n_C);
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
    /*int t=tailleSac(my_board);*/
    for (int i = 0; i <4 ; i++) {
        printf("Tétrimino %d : Type %d, Points %d\n", get_id(tetrominos[i]), get_type(tetrominos[i]), get_nb_points(tetrominos[i]));
    }
    printf("\n");

    // Affichage du score actuel
    printf("\nScore actuel : %d\n", get_score(my_board));
}

//la fonction  select_tetromino_on_grid
tetromino select_tetromino_on_grid(board my_board) {
    // Demande à la joueuse de sélectionner un tétromino sur la grille
    printf("Veuillez choisir un tétromino de la grille pour cela \n");
    printf("Veuillez saisir un entier naturel nombre de la colone \n");
    int c = -1;
    int r = -1;
    scanf("%d", &c);
    while (c < 0) {
        printf("Veuillez ressaisir un entier positif\n");
        scanf("%d", &c);
    }
    scanf("%d", &r);
    printf("Veuillez saisir un entier naturel nombre de la ligne \n");
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
    int taille=tailleSac(board);
    for (int i = 0; i <taille ; i++) {
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
    *r=-1;
    *c=-1;
    printf("Veuillez choisir une valeur de colonne [entier naturel] : \n");
    scanf("%d", c);
    printf("Veuillez choisir une valeur de ligne [entier naturel] : \n");
    scanf("%d", r);
     place_tetromino(board, *r, *c, tetromino);
    
}
// la fonction display_end_game 
void display_end_game(board board) {
    // Affiche un message de fin de jeu avec les informations associées
    printf("Fin du jeu\n");
    display_board( board );

}
// la fonction display_message
void display_message(char* message) {
    // Affiche le message donné en entrée
    printf("%s\n", message);
}

