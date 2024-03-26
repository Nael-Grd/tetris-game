<<<<<<< HEAD
#include "tetromino.h"
#include <stdlib.h>

typedef struct s_t {
=======
#include "../include/tetromino.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct s_t {
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
    int* forme;
    int type;
    int points;
    int id;
<<<<<<< HEAD
} s_t;
=======
};
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585

int identifiant=0;

tetromino create_tetromino(int t, int o, int p){
<<<<<<< HEAD
    if(t<0 || t>6 || p<1 || p>3){//vérifie la validité des paramètres
        printf("erreur: paramètres pour création de tetromino non valides");
        exit(1);
    }
    tetromino tet;
=======
    if(t<0 || t>6 || p<1 || p>3){
        printf("erreur: paramètres pour création de tetromino non valides");
        exit(1);
    }
    tetromino tet=malloc(sizeof(struct s_t));
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
    tet->type=t;
    tet->id=identifiant;
    identifiant++;
    tet->points=p;
    tet->forme=calloc(8,sizeof(int));
<<<<<<< HEAD
    for (int i=0; i<4;i++) tet->forme[i]=calloc(4,sizeof(int));
    switch(t){//On remplit forme des coordonnées des cases
        case 0:{//I-tetromino
=======
    switch(t){
        case 0:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%2==0){
                for (int j=1; j<4;j++){
                    tet->forme[2*j+1]=tet->forme[2*j-1]-1;
                }
            }
            else{
                for (int j=1; j<4;j++){
                    tet->forme[2*j+2]=tet->forme[2*j]+1;
                }
            }
        }
<<<<<<< HEAD
        case 1:{//O-tetromino
=======
        break;
        case 1:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            tet->forme[2]=-1;
            tet->forme[5]=-1;
            tet->forme[6]=-1;
            tet->forme[7]=-1;
        }
<<<<<<< HEAD
        case 2:{//T-tetromino
=======
        break;
        case 2:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%4==0){
                tet->forme[2]=-1;tet->forme[3]=-1;
                tet->forme[4]=-1;
                tet->forme[6]=-1;tet->forme[7]=1;
            }
            else if(o%4==1){
                tet->forme[2]=-1;tet->forme[3]=-1;
                tet->forme[4]=-1;
                tet->forme[6]=-2;
            }
            else if(o%4==2){
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[7]=2;
            }
            else{
                tet->forme[2]=-1;tet->forme[3]=-1;
                tet->forme[4]=1;
                tet->forme[6]=-2;
            }
        }
<<<<<<< HEAD
        case 3:{//L-tetromino
=======
        break;
        case 3:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%4==0){
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-1;tet->forme[7]=2;
            }
            else if(o%4==1){
                tet->forme[2]=-1;
                tet->forme[4]=-2;
                tet->forme[6]=-2;tet->forme[7]=-1;
            }
            else if(o%4==2){
                tet->forme[3]=1;
                tet->forme[5]=2;
                tet->forme[7]=2;tet->forme[6]=-1;
            }
            else{
                tet->forme[3]=-1;
                tet->forme[4]=-1;
                tet->forme[6]=-2;
            }
        }
<<<<<<< HEAD
        case 4:{//J-tetromino
=======
        break;
        case 4:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%4==0){
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=-1;
                tet->forme[6]=-1;tet->forme[7]=-2;
            }
            else if(o%4==1){
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-2;tet->forme[7]=1;
            }
            else if(o%4==2){
                tet->forme[2]=-1;
                tet->forme[5]=1;
                tet->forme[7]=2;
            }
            else{
                tet->forme[3]=-1;
                tet->forme[5]=-2;
                tet->forme[6]=1;tet->forme[7]=-2;
            }
        }
<<<<<<< HEAD
        case 5:{//S-tetromino
=======
        break;
        case 5:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%2==0){
                tet->forme[3]=1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-1;tet->forme[7]=2;
            }
            else if(o%2==1){
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=-1;
                tet->forme[6]=-2;tet->forme[7]=-1;
            }
        }
<<<<<<< HEAD
        case 6:{//Z-tetromino
=======
        break;
        case 6:{
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
            if(o%2==0){
                tet->forme[3]=1;
                tet->forme[4]=-1;
                tet->forme[6]=-1;tet->forme[7]=-1;
            }
            else if(o%2==1){
                tet->forme[2]=-1;
                tet->forme[4]=-1;tet->forme[5]=1;
                tet->forme[6]=-2;tet->forme[7]=1;
            }
        }
<<<<<<< HEAD
=======
        break;
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
    }
    return tet;    
}
tetromino create_random_tetromino(){
<<<<<<< HEAD
    int p=-1,t=-1;
    int o=rand(); 
    while(p<1 || p>3){
        p=rand();
    }
    while(t<0||t>6){
        t=rand();
    }
=======
    int p=((int)srand(time(NULL))%3)+1;  
    int t=(int)srand(time(NULL))%7; 
    int o=(int)srand(time(NULL))%4;
>>>>>>> a8a9e24a07ea2908a2154def4606e17034dc0585
    return create_tetromino(t,o,p);
}

void free_tetromino(tetromino tet){
    free(tet->forme);
    free(tet);
}

int get_type(tetromino tet){
    return tet->type;
}

int get_nb_points(tetromino tet){
    return tet->points;
}

int get_id(tetromino tet){
    return tet->id;
}

int* get_cells(tetromino tet){
    return tet->forme;
}
