#include "../../include/board.h"
#include "deepest_fit.h"
#include <stdlib.h>

/* @requires : board b, tetromino t, L the row f all the lower empty places
   @asssigns : L
   @ensures :  returning an array of all the lower empty places represented by t's id*/
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

/* @requires : board b, tetromino t,C and L the column and the row f all the lower empty places and taille its width
   @asssigns : C, L, and taille
   @ensures :  returning an array of all the lower empty places represented by t's id*/
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
    for(int i=0; i<get_nbLignes(b);i++)
        free(bas[i]);
    free(bas);
    free_board(aux);
    
    return plus_petit;
}

/* @requires : board b, C and L the column and the row f all the lower empty places and taille its width
   @asssigns : C, L, and taille
   @ensures :  returning the index of the tetromino that minimizes the highest occupiable spot*/
int piece_min(board b, int* C, int* L, int* taille){  //
    tetromino* le_sac=list_tetrominos_in_bag(b);
    int l=get_nbLignes(b); int c=nbColonnes(b);
    int haut_max=0;
    int piece_min=0;

    for(int i=0; i<4; i++) {    //pour chaque tetromino
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



int deepest_fit(board b) {
    int C; int L; int taille;
    int indice=piece_min(b,&C,&L,&taille);   //est fait l'appel a plus_petit pour modifier L et C
    int moitie=nbColonnes(b)/2;
    tetromino* le_sac=list_tetrominos_in_bag(b);
    if(C<moitie){
        place_tetromino(b, L, C, le_sac[indice]);
        for(int i=0;i<4;i++)
            free_tetromino(le_sac[i]);
        free(sac);
        return indice;
    }
    else{
        while(!place_tetromino(b, L, C+taille-1,le_sac[indice])) {
            taille--;                              //cas ou il est n'est pas placable tout a droite alors on decale
            if(check_place_tetromino(b, L, C+taille-1,le_sac[indice]))
            return indice;
        }
    }

}