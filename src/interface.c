#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/carte.h"


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
    tetromino reserve=list_reserve(my_board);
    if(reserve==NULL){
        printf("la réserve est vide.\n");
    }
    else{
        printf("Tétrimino %d : Type %d, Points %d\n", get_id(reserve), get_type(reserve), get_nb_points(reserve));
        display_tetromino(reserve);
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


/*Début de l'adaptation d'interface.c  de la Tache E4 faite par "ALI DAOUDI" */

/**
 * @brief Displays the details of a special card.
 *
 * @param cte The special card to display.
 */
void show_card(carte cte) {
    printf("\n\n << Card Name: %s \n    Description: %s >>\n\n", get_name_card(cte), get_info_carte(cte));
}

/**
 * @brief Applies the necessary effect when a card is used.
 *
 * @param b The game board.
 * @param c The index of the card to use.
 */
void to_need_to_use_card(board* b, int c) {
    carte* list_cte = get_list_card(*b);
    if (!list_cte[c]) return;
    
    int n = get_num(list_cte[c]);
    switch (n) {
        case 0:
            printf("Select the tetromino you want to remove\n");
            use_card(list_cte[c], b, -1, NULL);
            break;
        case 1:
        case 2:
            if (reserve_is_empty(*b)) {
                printf("\n Card without effect, empty reservoir! \n");
            } else {
                use_card(list_cte[c], b, n, NULL);
            }
            break;
        case 3:
            printf("\n<< Select tetrominos to remove, as many as you want >>\n\n");
            while (tetromino_in_board(*b)) {
                tetromino tr = select_tetromino_on_grid(*b);
                if (!tr) break;
                add_to_score(b, -1);
                use_card(list_cte[c], b, -1, tr);
            }
            if (!tetromino_in_board(*b)) printf("Empty board, cannot remove another tetromino\n");
            break;
        case 5:
            if (reserve_is_empty(*b)) {
                printf("\n Card without effect, empty reservoir! \n");
            } else {
                printf("Select the tetromino you want to exchange:\n");
                tetromino* sac = list_tetrominos_in_bag(*b);
                if (!sac) break;
                int c;
                scanf("%d", &c);
                if (c < 1 || c > 4) break;
                use_card(list_cte[c], b, -1, sac[c-1]);
            }
            break;
        case 6:
            if (reserve_is_full(*b)) {
                printf("\n Card without effect, full reservoir! \n");
            } else {
                use_card(list_cte[c], b, n, NULL);
            }
            break;
        case 7:
            printf("\n<< Select up to 3 tetrominos to remove while the board is not empty >>\n\n");
            for (int i = 0; i < 3 && tetromino_in_board(*b); i++) {
                tetromino tr = select_tetromino_on_grid(*b);
                if (!tr) break;
                add_to_score(b, get_nb_points(tr));
                use_card(list_cte[c], b, -1, tr);
            }
            break;
        case 8:
        case 16:
            use_card(list_cte[c], b, -1, NULL);
            break;
        case 14:
            printf("<< Select a tetromino (number) >>\n");
            int t;
            scanf("%d", &t);
            if (t >= 1 && t <= (*b)->k) {
                use_card(list_cte[c], b, t - 1, NULL);
            }
            break;
        case 17:
            printf("<< Expanding your bag by +1 >> \n");
            use_card(list_cte[c], b, -1, NULL);
            break;
        default:
            break;
    }
    remove_card(b, get_num(list_cte[c]));
}

/**
 * @brief Prompts the user to use a special card.
 *
 * @param b The game board.
 */
void ask_use_card(board* b) {
    carte* list_cte = get_list_card(*b);
    if (!list_cte) return;
    
    printf("\nDo you want to use a special card? \n");
    printf("0: No / 1: Yes \n");
    int c;
    printf("\nEnter your choice: ");
    scanf("%d", &c);
    
    bool has_card = false;
    for (int i = 0; i < 8; i++) {
        if (list_cte[i]) {
            has_card = true;
            break;
        }
    }
    
    if (c == 1 && has_card) {
        printf("\n<< List of available cards >>\n\n");
        for (int i = 0; i < 8; i++) {
            if (list_cte[i]) {
                printf("Special card no.: %d", i);
                show_card(list_cte[i]);
            }
        }
        printf("Enter the card number you want to use:\n");
        scanf("%d", &c);
        if (c >= 0 && c < 8) {
            to_need_to_use_card(b, c);
        }
    } else if (!has_card) {
        printf("\nUnable to choose a special card, you have none!\n\n");
    }
}
/*FIN de la Partie d'adaptation de la Tache:E4 pour interface .c faite par "ALI DAOUDI"*/
