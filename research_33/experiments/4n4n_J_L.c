#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deepest_fit.h"
#include "../../include/board.h"
#include "../../include/tetromino.h"


int main(){
    printf("expérience 4n*4n:\n");
    srand(time(NULL));
    double temps[20]; // on stocke le temps de l'expérence en fonction de n
    int scores[20]; // on stocke le score de l'expérience en fonction de n
    clock_t start, end;
    int en_cours=1; // c'est la variable qui assure l'arrêt chaque expérience
    for(int n=1; n<=20; n++){
        start=clock(); // on stocke le temps de départ de l'expérience
        board b=create_board(4*n,4*n,4); // on crée le bord de taille 4n*4n
        en_cours=1; 
        int tailleSac=4; // c'est la variable qui indique l'espace restant dans le sac
        while(en_cours){ // on commence
            while(tailleSac>0){ // on ajoute des tetrominos de type 3 ou 4
                add_tetromino_to_bag(b,create_tetromino(rand()%2==1? 4:3,0,rand()%3+1)); 
                tailleSac--;
            }
            tetromino* sacs=list_tetrominos_in_bag(b); // on les récupère
            int indice=deepest_fit(b); // on fait le deepest fit
            printf("%d \n", indice);
            if (indice==-1) en_cours=0; // on arrete lorsque le bord est plein/n'a plus de place pour les tetrominos
            else {
                remove_tetromino_from_bag(b,sacs[indice]); // on enlève le tetromino qu'on vient de placer
                tailleSac++;
            }
            for(int i=0;i<4;i++){
                free_tetromino(sacs[i]);
            }
            free(sacs);
        }
        scores[n-1]=get_score(b); // on ajoute le score dans le tableau
        free_board(b); 
        end=clock(); // on stocke le temps d'arrêt de l'expérience
        temps[n-1]=(double)(end-start)/(double)CLOCKS_PER_SEC; // on calcule et stocke le temps de l'expérience 
    }
    printf("le tableau de valeurs:\n"); // affichage des valeurs
    printf("n ");
    for(int i=1;i<=20;i++)
        printf("%d ",i);
    printf("\n");
    printf("temps ");
    for(int i=0; i<20;i++)
        printf("%lf ",temps[i]);
    printf("\n");
    printf("score ");
    for(int i=0; i<20;i++)
        printf("%d ",scores[i]);
    return 0;
}