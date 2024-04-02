#include "../../include/board.h"
#include "deepest_fit.h"
#include <stdlib.h>


int** plus_bas(tetromino t, board b, int* L){
    int l=get_nbLignes(b); int c=nbColonnes(b);
    board aux=create_board(l,c,1); // initialisation d'un board auxiliaire
    // parcours du board
    *L=0;
    for (int i=0; i<l;i++){ 
        for (int j=0; j<c; j++){
            if(check_place_tetromino(b,i,j,t) && i>*L){ 
                *L=i;
            }
        }
    }
    for (int j=0; j<c; j++){ // on place le tetromino dans ces espaces libres
        place_tetromino(aux,*L,j,t);
    }
    int** espaces_libres_plus_bas= grille(aux);
    free_board(aux);
    return espaces_libres_plus_bas;
}

int** plus_petit(tetromino t, board b, int* C, int* L, int* taille){  
    int **bas=plus_bas(t,b,L);
    *taille=nbColonnes(b)+1;
    *C=0;
    for(int j=0; j<nbColonnes(b); j++){
        int cpt=0;
        if(bas[*L][j]!=0){   //si on trouve le debut d'un espace libre
            cpt++;
            int k=j+1;
            while(bas[*L][k]!=0 && k<nbColonnes(b)){ //on cherche la suite de l'espace libre en s'arrettant au max
                cpt++;
                k++; j++;
            }
            if(*taille>cpt){     //on compare l'espace trouvé au plus petit trouvé auparavant
                *C=j;
                *taille=cpt;
            }
        }
    }
    board aux=create_board(get_nbLignes(b),nbColonnes(b),1);    //on créé un nouveau tableau pour y placer l'unique plus petit espace
    for(int h=0;h<*taille;h++){
        if(check_place_tetromino(b,*L,*C-h,t)){
            place_tetromino(aux,*L,*C,t);
            *C--;
        }
    }
    *C++;
    int** plus_petit=grille(aux);
    free_board(aux);
    return plus_petit;
}

int piece_min(board b, int* C, int* L, int* taille){  //
    tetromino* le_sac=sac(b);
    int l=get_nbLignes(b); int c=nbColonnes(b);
    int haut_max=0;
    int piece_min=0;

    for(int i=0; i<tailleSac(b); i++) {    //pour chaque tetromino
        int case_haute=-1;
        int* C_i; int* L_i; int* taille_i;
        int haut_max=0;
        int** petit = plus_petit(le_sac[i], b, C_i, L_i, taille_i);
        int h=0;
        while(case_haute<0){
            for(int j=0; j<c; j++) {
                if(petit[h][j]!=0){
                    case_haute=h;   //stock la case la plus haute pour chaque tetro
                    break;    
                }
            }
            h++;
        }
        if (haut_max < case_haute) {    //prend la hauteur minimum des 4 tetros
            haut_max=case_haute;
            piece_min = i;
            *C=*C_i; *L=*L_i; *taille=*taille_i; // on stock la case la plus basse à gauche de l'espace vide
        }
        for(int i=0;i<get_nbLignes(b);i++){
            free(petit[i]);
        }
        free(plus_petit);
    }
    return piece_min;
}



void deepest_fit(board b) {
    int C; int L; int taille;
    int indice=piece_min(b,&C,&L,&taille);   //est fait l'appel a plus_petit pour modifier L et C
    int moitie=nbColonnes(b)/2;
    tetromino* le_sac=sac(b);
    if(C<moitie){
        place_tetromino(b, L, C, le_sac[indice]);
    }
    else{
        while(!place_tetromino(b, L, C+taille-1,le_sac[indice])) {
            taille--;                              //cas ou il est n'est pas placable tout a droite alors on decale
        }
    }

}