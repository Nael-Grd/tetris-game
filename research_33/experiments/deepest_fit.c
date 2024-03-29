#include "../../include/board.h"
#include "deepest_fit.h"

#define IMPLACABLE 1000

int* min_hauteur_tetromino(board b, tetromino t){
    int r=0;   //ligne
    int c=0;   //colonne
    int tab[2];
    while (!check_place_tetromino(b ,r, c, t)) {  //tant qu'on n'a pas trouvé la case la plus en haut
        if(c==nbColonnes(b)-1){           //arriver en bout de ligne
            c=0;
            r++;
            if(r==get_nbLignes(b)){        //quand la grille a été totalement parcourue
                tab[0]=IMPLACABLE;
                tab[1]=IMPLACABLE;
                return tab;
            }
        }
        else{
            c++;
        }
    }
    tab[0]=r;
    tab[1]=c;
    return tab;
}

int* deepest_fit(board b){
    int r=IMPLACABLE;
    int indice=-1;
    int valeurs[3];
    tetromino* sac=sac(b);
    for(int i=0; i<tailleSac(b); i++){
        if(r>=min_hauteur_tetromino(b, sac[i])[0]){
            r=min_hauteur_tetromino(b, sac[i])[0];
            indice=i;
        }
    }
    if (place_tetromino(b, r, c, sac[indice])) {  
        valeurs[0]=min_hauteur_tetromino(b, sac[indice])[0];
        valeurs[1]=min_hauteur_tetromino(b, sac[indice])[1];
        valeurs[2]=indice;
    }
    else {
        return 
    }
}