#include "../include/tetromino.h"
#include <stdio.h>
#include <stdlib.h>

struct s_t {
    int* forme; /* un tableau de 8 valeurs. chaque 2 valeurs sont 
            les coordonnées (y descendant, x ascendant) d'une case du tetromino*/
    int type; /* les types indiquent la forme du tetromino:
                0->I
                1->O
                2->T
                3->L
                4->J
                5->S
                6->Z*/
    int points; /* ce sont les points que placer le tetromino 
            ajoute au score */
    int id; // l'identifiant unique de chaque tetromino
};

int identifiant=1;

tetromino create_tetromino(int t, int o, int p){
    if(t<0 || t>6 || p<1 || p>3){
        printf("erreur: paramètres pour création de tetromino non valides");
        exit(1);
    }
    tetromino tet=malloc(sizeof(struct s_t));
    if(tet==NULL){
        printf("allocation du tetromino échouée\n");
        exit(2);
    }
    tet->type=t;
    tet->id=identifiant;
    identifiant++;
    tet->points=p;
    tet->forme=calloc(8,sizeof(int));
    if(tet==NULL){
        printf("allocation du tableau du tetromino échouée\n");
        exit(3);
    }
    switch(t){
        /* ce n'est pas possible d'utiliser une boucle pr remplir le tableau "forme" 
        donc on fait un traitement cas par cas*/
        case 0:{ // I
            if(o%2==0){ // debout
                for (int j=1; j<4;j++){
                    tet->forme[2*j]=tet->forme[2*j-2]-1;
                }
            }
            else{ // allongé
                for (int j=1; j<4;j++){
                    tet->forme[2*j+1]=tet->forme[2*j-1]+1;
                }
            }
        }
        break;
        case 1:{// O
            tet->forme[2]=-1;
            tet->forme[5]=1;
            tet->forme[6]=-1;
            tet->forme[7]=1;
        }
        break;
        case 2:{ // T
            if(o%4==0){ // debout 
                tet->forme[2]=-1;tet->forme[3]=-1;
                tet->forme[4]=-1;
                tet->forme[6]=-1;tet->forme[7]=1;
            }
            else if(o%4==1){ // tourné à 90 degrés
                tet->forme[2]=-1;tet->forme[3]=-1;
                tet->forme[4]=-1;
                tet->forme[6]=-2;
            }
            else if(o%4==2){ // tourné à 180 degrés
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[7]=2;
            }
            else{ // tourné à 270 degrés
                tet->forme[2]=-1;tet->forme[3]=1;
                tet->forme[4]=-1;
                tet->forme[6]=-2;
            }
        }
        break;
        case 3:{ // L
            if(o%4==1){ // tourné à 90 degrés
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-1;tet->forme[7]=2;
            }
            else if(o%4==2){ // tourné à 180 degrés
                tet->forme[2]=-1;
                tet->forme[4]=-2;
                tet->forme[6]=-2;tet->forme[7]=-1;
            }
            else if(o%4==3){ // tourné à 270 degrés
                tet->forme[3]=1;
                tet->forme[5]=2;
                tet->forme[7]=2;tet->forme[6]=-1;
            }
            else{ // debout
                tet->forme[3]=1;
                tet->forme[4]=-1;
                tet->forme[6]=-2;
            }
        }
        break;
        case 4:{ // J
            if(o%4==3){ // tourné à 270 degrés
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=-1;
                tet->forme[6]=-1;tet->forme[7]=-2;
            }
            else if(o%4==0){ // debout
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-2;tet->forme[7]=1;
            }
            else if(o%4==1){ // tourné à 90 degrés
                tet->forme[2]=-1;
                tet->forme[5]=1;
                tet->forme[7]=2;
            }
            else{ // tourné à 180 degrés
                tet->forme[2]=-1;
                tet->forme[4]=-2;
                tet->forme[7]=1;tet->forme[6]=-2;
            }
        }
        break;
        case 5:{ // S
            if(o%2==0){ // debout
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-1;tet->forme[7]=2;
            }
            else if(o%2==1){ // tourné
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=-1;
                tet->forme[6]=-2;tet->forme[7]=-1;
            }
        }
        break;
        case 6:{ // Z
            if(o%2==0){ // debout
                tet->forme[3]=1;
                tet->forme[4]=-1;
                tet->forme[6]=-1;tet->forme[7]=-1;
            }
            else if(o%2==1){ // tourné
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-2;tet->forme[7]=1;
            }
        }
        break;
    }
    return tet;    
}
tetromino create_random_tetromino(){ // on utilise la fonction rand() mais on suspecte qu'il y a mieux...
    int p=(rand()%3)+1; // nb de points aléatoire entre 1 et 3
    int t=rand()%7;  // type aléatoire entre 0 et 6
    int o=rand()%4; // orientation aléatoire entre 0 et 3
    return create_tetromino(t,o,p);
}

void free_tetromino(tetromino tet){ // puisque on alloue le tetromino et forme dynamiquement on les libère
    if(tet!=NULL){
        if(tet->forme!=NULL) free(tet->forme);
        free(tet);
    }
}

int get_type(tetromino tet){ // ceci renvoi le composant "type" (un entier qui indique le type) de la structure tetromino
    if(tet==NULL){
        printf("pas possible de récupérer le type d'un tetromino null\n");
        exit(4);
    }
    return tet->type;
}

int get_nb_points(tetromino tet){ /* ceci renvoi le composant "points" (un entier qui indique les points) 
                                    de la structure tetromino*/
    if(tet==NULL){
        printf("pas possible de récupérer les points d'un tetromino null\n");
        exit(5);
    }
    return tet->points;
}

int get_id(tetromino tet){ // ceci renvoi l'id du tetromino
    if(tet==NULL){
        printf("pas possible de récupérer l'id d'un tetromino null\n");
        exit(6);
    }
    return tet->id;
}

int* get_cells(tetromino tet){ // ceci renvoi le tableau des coordonnées des composants du tetromino
    if(tet==NULL){
        printf("pas possible de récupérer les cells d'un tetromino null\n");
        exit(7);
    }
    return tet->forme;
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
