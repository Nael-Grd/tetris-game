#include "../include/tetromino.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct s_t {
    int* forme;
    int type;
    int points;
    int id;
};

int identifiant=0;

tetromino create_tetromino(int t, int o, int p){
    if(t<0 || t>6 || p<1 || p>3){
        printf("erreur: paramètres pour création de tetromino non valides");
        exit(1);
    }
    tetromino tet=malloc(sizeof(struct s_t));
    tet->type=t;
    tet->id=identifiant;
    identifiant++;
    tet->points=p;
    tet->forme=calloc(8,sizeof(int));
    switch(t){
        case 0:{
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
        break;
        case 1:{
            tet->forme[2]=-1;
            tet->forme[5]=-1;
            tet->forme[6]=-1;
            tet->forme[7]=-1;
        }
        break;
        case 2:{
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
        break;
        case 3:{
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
        break;
        case 4:{
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
        break;
        case 5:{
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
        break;
        case 6:{
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
        break;
    }
    return tet;    
}
tetromino create_random_tetromino(){
    int p=(rand()%3)+1;  
    int t=rand()%7; 
    int o=rand()%4;
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
