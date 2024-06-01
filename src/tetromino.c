#include "../include/tetromino.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Structure représentant un tétrimino.
 */
struct s_t {
    int* forme;
    int type; /**< les types indiquent la forme du tetromino:
                0->I, 1->O, 2->T, 3->L, 4->J, 5->S, 6->Z */
    int points; /**< Points que placer le tetromino ajoute au score */
    int orientation;
    int id; /**< Identifiant unique de chaque tetromino */
};

int identifiant = 1;

/**
 * @brief Crée un nouveau tétrimino avec les paramètres spécifiés.
 *
 * @param t Type de tétrimino (de 0 à 6).
 * @param o Orientation initiale du tétrimino (de 0 à 3).
 * @param p Nombre de points que le tétrimino ajoute au score.
 * @return Pointeur vers le tétrimino nouvellement créé.
 */
tetromino create_tetromino(int t, int o, int p) {
    if (t < 0 || t > 6 || p < 1 || p > 3) {
        printf("erreur: paramètres pour création de tetromino non valides");
        exit(1);
    }
    tetromino tet = malloc(sizeof(struct s_t));
    if (tet == NULL) {
        printf("allocation du tetromino échouée\n");
        exit(2);
    }
    tet->type = t;
    tet->id = identifiant++;
    tet->orientation = o;
    tet->points = p;
    tet->forme = malloc(8 * sizeof(int));
    switch (t) {
        case 0: { // Tétrimino I
            if (o % 2 == 0) {
                for (int j = 1; j < 4; j++) {
                    tet->forme[2 * j] = tet->forme[2 * j - 2] - 1;
                }
            } else {
                for (int j = 1; j < 4; j++) {
                    tet->forme[2 * j + 1] = tet->forme[2 * j - 1] + 1;
                }
            }
        } break;
        case 1: { // Tétrimino O
            tet->forme[2] = -1;
            tet->forme[5] = 1;
            tet->forme[6] = -1;
            tet->forme[7] = 1;
        } break;
        case 2: { // Tétrimino T
            if (o % 4 == 0) {
                tet->forme[2] = -1; tet->forme[3] = -1;
                tet->forme[4] = -1;
                tet->forme[6] = -1; tet->forme[7] = 1;
            } else if (o % 4 == 1) {
                tet->forme[2] = -1; tet->forme[3] = -1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            } else if (o % 4 == 2) {
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[7] = 2;
            } else {
                tet->forme[2] = -1; tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            }
        } break;
        case 3: { // Tétrimino L
            if (o % 4 == 1) {
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -1; tet->forme[7] = 2;
            } else if (o % 4 == 2) {
                tet->forme[2] = -1;
                tet->forme[4] = -2;
                tet->forme[6] = -2; tet->forme[7] = -1;
            } else if (o % 4 == 3) {
                tet->forme[3] = 1;
                tet->forme[5] = 2;
                tet->forme[7] = 2; tet->forme[6] = -1;
            } else {
                tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            }
        } break;
        case 4: { // Tétrimino J
            if (o % 4 == 3) {
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = -1;
                tet->forme[6] = -1; tet->forme[7] = -2;
            } else if (o % 4 == 0) {
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -2; tet->forme[7] = 1;
            } else if (o % 4 == 1) {
                tet->forme[2] = -1;
                tet->forme[5] = 1;
                tet->forme[7] = 2;
            } else {
                tet->forme[2] = -1;
                tet->forme[4] = -2;
                tet->forme[7] = 1; tet->forme[6] = -2;
            }
        } break;
        case 5: { // Tétrimino S
            if (o % 2 == 0) {
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -1; tet->forme[7] = 2;
            } else if (o % 2 == 1) {
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = -1;
                tet->forme[6] = -2; tet->forme[7] = -1;
            }
        } break;
        case 6: { // Tétrimino Z
            if (o % 2 == 0) {
                tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -1; tet->forme[7] = -1;
            } else if (o % 2 == 1) {
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -2; tet->forme[7] = 1;
            }
        } break;
    }
    return tet;
}

/**
 * @brief Crée un tétrimino aléatoire.
 *
 * @return Pointeur vers le tétrimino nouvellement créé.
 */
tetromino create_random_tetromino() {
    int p = (rand() % 3) + 1; // nb de points aléatoire entre 1 et 3
    int t = rand() % 7;  // type aléatoire entre 0 et 6
    int o = rand() % 4; // orientation aléatoire entre 0 et 3
    return create_tetromino(t, o, p);
}

/**
 * @brief Libère la mémoire allouée pour un tétrimino.
 *
 * @param tet Pointeur vers le tétrimino à libérer.
 */
void free_tetromino(tetromino tet) {
    if (tet != NULL) {
        free(tet);
    }
}

/**
 * @brief Obtient le type d'un tétrimino.
 *
 * @param tet Pointeur vers le tétrimino dont on veut obtenir le type.
 * @return Le type du tétrimino.
 */
int get_type(tetromino tet) {
    if (tet == NULL) {
        printf("pas possible de récupérer le type d'un tetromino null\n");
        exit(4);
    }
    return tet->type;
}

/**
 * @brief Obtient le nombre de points d'un tétrimino.
 *
 * @param tet Pointeur vers le tétrimino dont on veut obtenir les points.
 * @return Le nombre de points du tétrimino.
 */
int get_nb_points(tetromino tet) {
    if (tet == NULL) {
        printf("pas possible de récupérer les points d'un tetromino null\n");
        exit(5);
    }
    return tet->points;
}

/**
 * @brief Obtient l'identifiant d'un tétrimino.
 *
 * @param tet Pointeur vers le tétrimino dont on veut obtenir l'identifiant.
 * @return L'identifiant du tétrimino.
 */
int get_id(tetromino tet) {
    if (tet == NULL) {
        printf("pas possible de récupérer l'id d'un tetromino null\n");
        exit(6);
    }
    return tet->id;
}


void display_tetromino(tetromino t){ // ceci affiche le tetromino
    int taille=6;
    // créer la mini grille qui est de 6 lignes et 6 colonnes
    char** mini_grille=malloc(taille*sizeof(char*));
    if(mini_grille==NULL){
        printf("erreur d'allocation de la mini grille\n");
        exit(8);
    }
    for (int i=0;i<taille;i++){
        mini_grille[i]=malloc(taille*sizeof(char));
        if(mini_grille[i]==NULL){
            printf("erreur d'allocation de la mini grille %d\n",i);
            exit(9+i);
        }
    }
    for(int h=0; h<taille;h++){
        for(int k=0; k<taille; k++){
            mini_grille[h][k]='-';
        }
    }
    // la remplir par le tetromino: on commence par la case à la 5eme ligne et la 3ème colonne
    int* cells=get_cells(t);
    int l=4;
    int c=2;
    for (int j=0;j<8;j+=2){
        if(cells[j]==0 && cells[j+1]==0){
            mini_grille[l+cells[j]][c+cells[j+1]]='X';
        }
        else{
            mini_grille[l+cells[j]][c+cells[j+1]]='O';
        }
    }
    for (int m=0;m<taille;m++){
        for(int n=0;n<taille;n++){
            printf("%c ",mini_grille[m][n]);
        }
        printf("\n");
    }
    for(int z=0;z<taille;z++){
        free(mini_grille[z]);
    }
    free(mini_grille);
}






/* @note: cette partie est dédié pour la gestion de la tache E.2 */







/**
 * @brief Obtient l'orientation d'un tétrimino.
 *
 * @param tet Pointeur vers le tétrimino dont on veut obtenir l'orientation.
 * @return L'orientation du tétrimino.
 */
int get_orientation(tetromino tet) {
    if (tet == NULL) {
        printf("pas possible de récupérer l'orientation d'un tetromino null\n");
        exit(7);
    }
    return tet->orientation;
}



/**
 * @brief Faire pivoter le tétrimino donné d'un incrément spécifié.
 *
 * @param tet Pointeur vers le tétrimino à faire pivoter.
 * @param increment La valeur d'incrémentation de la rotation du tétrimino.
 */
void rotate_tetromino(tetromino tet, int increment) {
    // Si l'incrément est nul, ne rien faire
    if (increment == 0) return;

    // Mettre à jour l'orientation du tétrimino
    tet->orientation += increment;
    
    int typeTetromino = tet->type;
    int orientationTetromino = tet->orientation;
    
    // Réinitialiser la forme du tétrimino
    for (int i = 0; i < 8; i++) {
        tet->forme[i] = 0;
    }
    
    // Traiter chaque type de tétrimino individuellement
    switch (typeTetromino) {
        case 0: { // Tétrimino I
            if (orientationTetromino % 2 == 0) { // Vertical
                for (int j = 1; j < 4; j++) {
                    tet->forme[2 * j] = tet->forme[2 * j - 2] - 1;
                }
            } else { // Horizontal
                for (int j = 1; j < 4; j++) {
                    tet->forme[2 * j + 1] = tet->forme[2 * j - 1] + 1;
                }
            }
        } break;
        
        case 1: { // Tétrimino O
            tet->forme[2] = -1;
            tet->forme[5] = 1;
            tet->forme[6] = -1;
            tet->forme[7] = 1;
        } break;
        
        case 2: { // Tétrimino T
            if (orientationTetromino % 4 == 0) { // Vertical
                tet->forme[2] = -1; tet->forme[3] = -1;
                tet->forme[4] = -1;
                tet->forme[6] = -1; tet->forme[7] = 1;
            } else if (orientationTetromino % 4 == 1) { // 90 degrés
                tet->forme[2] = -1; tet->forme[3] = -1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            } else if (orientationTetromino % 4 == 2) { // 180 degrés
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[7] = 2;
            } else { // 270 degrés
                tet->forme[2] = -1; tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            }
        } break;
        
        case 3: { // Tétrimino L
            if (orientationTetromino % 4 == 1) { // 90 degrés
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -1; tet->forme[7] = 2;
            } else if (orientationTetromino % 4 == 2) { // 180 degrés
                tet->forme[2] = -1;
                tet->forme[4] = -2;
                tet->forme[6] = -2; tet->forme[7] = -1;
            } else if (orientationTetromino % 4 == 3) { // 270 degrés
                tet->forme[3] = 1;
                tet->forme[5] = 2;
                tet->forme[7] = 2; tet->forme[6] = -1;
            } else { // Vertical
                tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -2;
            }
        } break;
        
        case 4: { // Tétrimino J
            if (orientationTetromino % 4 == 3) { // 270 degrés
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = -1;
                tet->forme[6] = -1; tet->forme[7] = -2;
            } else if (orientationTetromino % 4 == 0) { // Vertical
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -2; tet->forme[7] = 1;
            } else if (orientationTetromino % 4 == 1) { // 90 degrés
                tet->forme[2] = -1;
                tet->forme[5] = 1;
                tet->forme[7] = 2;
            } else { // 180 degrés
                tet->forme[2] = -1;
                tet->forme[4] = -2;
                tet->forme[7] = 1; tet->forme[6] = -2;
            }
        } break;
        
        case 5: { // Tétrimino S
            if (orientationTetromino % 2 == 0) { // Vertical
                tet->forme[3] = 1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -1; tet->forme[7] = 2;
            } else if (orientationTetromino % 2 == 1) { // Tourné
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = -1;
                tet->forme[6] = -2; tet->forme[7] = -1;
            }
        } break;
        
        case 6: { // Tétrimino Z
            if (orientationTetromino % 2 == 0) { // Vertical
                tet->forme[3] = 1;
                tet->forme[4] = -1;
                tet->forme[6] = -1; tet->forme[7] = -1;
            } else if (orientationTetromino % 2 == 1) { // Tourné
                tet->forme[2] = -1;
                tet->forme[4] = -1; tet->forme[5] = 1;
                tet->forme[6] = -2; tet->forme[7] = 1;
            }
        } break;
    }
}
