#include "../include/interface.h"
#include "../include/board.h"
#include <stdio.h>

// Fonction pour choisir l'action
int choose_action() {
    int action;
    char input[100];
    while (1) { //Tâche E3: ajouté l'option de la réserve
        printf("Voulez-vous arrêter le jeu ? Si oui, saisissez (0). Pour prendre un tetromino dans le sac et le placer, saisissez (1). Si vous voulez déplacer un tetromino présent sur la grille, saisissez (2). Pour placer le tetromino dans la réserve (s'il y en a), saisissez (3) : \n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &action) == 1) {
            return action;
        } else {
            printf("Entrée invalide. Veuillez saisir un entier.\n");
        }
    }
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
        display_tetromino(tetrominos[i]);
    }
    printf("\n");

    //tâche E2: affichage de la réserve
    printf("\nRéserve :\n");
    tetromino* reserve=list_reserve(my_board);
    if(reserve==NULL){
        printf("la réserve est vide.\n");
    }
    else{
        printf("Tétrimino %d : Type %d, Points %d\n", get_id(reserve[0]), get_type(reserve[0]), get_nb_points(reserve[0]));
        display_tetromino(reserve[0]);
    }

    // Affichage du score actuel
    printf("Score actuel : %d\n", get_score(my_board));
}

// Fonction pour sélectionner un tetromino sur la grille
tetromino select_tetromino_on_grid(board my_board) {
    char input[100];
    int c = -1, r = -1;
    while (1) {
        printf("Veuillez choisir un tetromino de la grille. Veuillez saisir un entier naturel pour le numéro de la colonne suivi par le numéro de ligne : \n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %d", &c, &r) == 2 && c >= 0 && r >= 0) {
            tetromino tet = get_tetromino(my_board, r, c);
            if (tet != NULL) {
                return tet;
            } else {
                printf("Aucun tetromino trouvé à cet emplacement. Veuillez réessayer.\n");
            }
        } else {
            printf("Entrée invalide. Veuillez saisir deux entiers positifs séparés par un espace.\n");
        }
    }
}
// Fonction pour sélectionner un tetromino dans le sac
tetromino select_tetromino_in_bag(board board) {
    char input[100];
    int c = -1;
    tetromino *tet;
    int taille = tailleSac(board);
    while (1) {
        printf("Veuillez choisir un tetromino dans le sac. Veuillez saisir un entier naturel pour l'identifiant : \n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &c) == 1 && c >= 0) {
            tet = list_tetrominos_in_bag(board);
            for (int i = 0; i < taille; i++) {
                if (get_id(tet[i]) == c) {
                    return tet[i];
                }
            }
            printf("tetromino avec cet identifiant non trouvé dans le sac. Veuillez réessayer.\n");
        } else {
            printf("Entrée invalide. Veuillez saisir un entier positif.\n");
        }
    }
}


// Fonction pour demander à l'utilisateur de placer un tetromino sur la grille
void ask_place_tetromino(board board, int* r, int* c, tetromino tetromino) {
    char input[100];
    while (1) {
        printf("Veuillez sélectionner une ligne et une colonne où placer le tetromino dans la grille. Veuillez saisir un entier naturel pour le numéro de colonne suivi par le numéro de ligne : \n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %d", c, r) == 2 && *c >= 0 && *r >= 0) {
            if (check_place_tetromino(board, *r, *c, tetromino)) {
                return;
            } else {
                printf("Emplacement déjà occupé. Veuillez sélectionner un autre emplacement.\n");
            }
        } else {
            printf("Entrée invalide. Veuillez saisir deux entiers positifs séparés par un espace.\n");
        }
    }
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
