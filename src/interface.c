#include "../include/interface.h"
#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/carte.h"
#include <stdio.h>


#define RESET       "\x1b[0m"  // Réinitialise les attributs de couleur et de style
#define BGWHITE     "\x1b[47m" // Définit le fond du texte à blanc
#define GRID_BORDER "██"


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
    printf("   ");
    for(int truc=0;truc<n_l;truc++)
        printf("%d  ",truc);
    printf("\n");
    for (int i = 0; i < n_l; i++) {
        printf("\n");
        printf("%d ",i);
        for (int j = 0; j < n_C; j++) {
            if (p[i][j]== 0) {
                printf(BGWHITE "  " RESET); // Case vide avec fond blanc
                printf(" ");
            } else {
                printf("\x1b[%dm" GRID_BORDER RESET, 31+(p[i][j]%6)); // Case colorée avec le code de couleur dynamique
                printf(" ");
            }
        }
        printf("\n");
    }

    // Affichage du sac de tétrominos en ligne
    printf("\nSac de tétrominos :\n");
    tetromino *tetrominos = list_tetrominos_in_bag(my_board);
    
    // Afficher les en-têtes
    for (int i = 0; i < 4; i++) {
        printf("Tétromino %d : Type %d, Points %d       ", 
               get_id(tetrominos[i]), get_type(tetrominos[i]), get_nb_points(tetrominos[i]));
    }
    printf("\n");
    
    // Afficher les 4 tétromino côte à côte (6 lignes de hauteur)
    for (int ligne = 0; ligne < 6; ligne++) {
        for (int i = 0; i < 4; i++) {
            // Créer et initialiser mini grille pour ce tétrimino
            char mini_grille[6][6];
            int taille = 6;
            
            for(int h = 0; h < taille; h++) {
                for(int k = 0; k < taille; k++) {
                    mini_grille[h][k] = '-';
                }
            }
            
            // Remplir avec le tétromino (même logique que display_tetromino)
            int* cells = get_cells(tetrominos[i]);
            int l = 4, c = 2;
            for (int j = 0; j < 8; j += 2) {
                if(cells[j] == 0 && cells[j+1] == 0) {
                    mini_grille[l + cells[j]][c + cells[j+1]] = 'X';
                } else {
                    mini_grille[l + cells[j]][c + cells[j+1]] = 'O';
                }
            }
            
            // Afficher cette ligne du tétromino avec les MÊMES couleurs
            for(int n = 0; n < taille; n++) {
                if(mini_grille[ligne][n] == '-') {
                    printf(BGWHITE "  " RESET);
                } else if(mini_grille[ligne][n] == 'X') {
                    printf("\x1b[%dm" GRID_BORDER RESET, 91);
                } else {
                    printf("\x1b[%dm" GRID_BORDER RESET, 31+(get_id(tetrominos[i])%6));
                }
            }
            printf("                         "); // Espace entre tétrominos
        }
        printf("\n"); // Nouvelle ligne après chaque rangée
    }
    printf("\n");
    

    //tâche E2: affichage de la réserve
    printf("\nRéserve :\n");
    tetromino reserve=list_reserve(my_board);
    if(reserve==NULL){
        printf("la réserve est vide.\n");
    }
    else{
        printf("Tétromino %d : Type %d, Points %d\n", get_id(reserve), get_type(reserve), get_nb_points(reserve));
        display_tetromino(reserve);
    }

    // Affichage du score actuel
    printf("\n");
    printf("Score actuel : %d\n", get_score(my_board));
    printf("\n");
}

// Fonction pour sélectionner un tetromino sur la grille
tetromino select_tetromino_on_grid(board my_board) {
    char input[100];
    int c = -1, r = -1;
    while (1) {
        printf("Veuillez choisir un tétromino de la grille. Veuillez saisir un entier naturel pour le numéro de la colonne suivi par le numéro de ligne : \n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d %d", &c, &r) == 2 && c >= 0 && r >= 0) {
            tetromino tet = get_tetromino(my_board, r, c);
            if (tet != NULL) {
                return tet;
            } else {
                printf("Aucun tétromino trouvé à cet emplacement. Veuillez réessayer.\n");
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
            printf("identifiant de tétromino non trouvé dans le sac. Veuillez réessayer.\n");
        } else {
            printf("Entrée invalide. Veuillez saisir un entier positif.\n");
        }
    }
}


// Fonction pour demander à l'utilisateur de placer un tetromino sur la grille
void ask_place_tetromino(board board, int* r, int* c, tetromino tetromino) {
    char input[100];
    while (1) {
        printf("Veuillez sélectionner une colonne et une ligne où placer le tétromino sur la grille. Veuillez saisir un entier naturel pour le numéro de colonne suivi par le numéro de ligne : \n");
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

void ask_rotate_tetromino(tetromino tetromino) {
    char input[100];
    while (1) {
        printf("Voulez-vous orienter le tetromino? Oui(Mettez de combien de fois) Non(0) \n");
        fgets(input, sizeof(input), stdin);
        int r;
        if (sscanf(input, "%d", &r) == 1) {
            rotate_tetromino(tetromino,r);
            return;
        }
        else{
            printf("entrée invalide!\n");
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


void display_carte(carte c){
    printf("Nom:%s\nEffet:%s\n",get_name_card(c),get_info_carte(c));
}

void ask_use_carte(board b){
    int act; char in[100];
    int truc=1;
    while(truc){
        printf("voulez-vous générer une carte? Oui(1) ou non(2)\n");
        fgets(in,sizeof(in),stdin);
        if(sscanf(in,"%d",&act)==1 && (act==1 || act==2)) truc =0;
        else printf("Entrée invalide. Veuillez saisir 1 ou 2\n");
    }
    if(act==1){
        carte c=create_carte();
        display_carte(c);
        int act2; char in2[100];
        int truc2=1;
        while(truc2){
            printf("voulez-vous utiliser la carte? Oui(1) ou non(2)\n");
            fgets(in2,sizeof(in2),stdin);
            if(sscanf(in2,"%d",&act2)==1 && (act2==1 || act2==2)) truc2 =0;
            else printf("Entrée invalide. Veuillez saisir 1 ou 2\n");
        }
        if(act2==1){
            switch(get_num(c)){
                case 8:
                    Christophe_Mouilleron(b);
                    break;
                case 0:
                    Thuy_Vo(b);
                    break;
                case 1:
                    David_Roussel(b);
                    break;
                case 2:
                    Abass_Sagna(b);
                    break;
                case 5:
                    Laurence_Bourard(b);
                    break;

            }
        }

    }
}
