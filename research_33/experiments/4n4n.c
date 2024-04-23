#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deepest_fit.h"
#include "../../include/board.h"
#include "../../include/tetromino.h"

// gcc -Wall -Wextra -std=c99 4n4n.c deepest_fit.c ../../src/board.c ../../src/tetromino.c -o 4n4n


int main(){
    printf("expérience 4n*4n:\n");
    srand(time(NULL));
    double temps[20];
    int scores[20];
    clock_t start, end;
    int en_cours=1;
    for(int n=1; n<=20; n++){
        start=clock();
        board b=create_board(4*n,4*n,4);
        en_cours=1;
        int tailleSac=4;
        while(en_cours){
            while(tailleSac>0){
                add_tetromino_to_bag(b,create_tetromino(rand()%2==1? 5:6,0,rand()%3+1));
                tailleSac--;
            }
            tetromino* sacs=list_tetrominos_in_bag(b);
            int indice=deepest_fit(b);
            printf("%d \n", indice);
            if (indice==-1) en_cours=0;
            else {
                remove_tetromino_from_bag(b,sacs[indice]);
                tailleSac++;
            }
            for(int i=0;i<4;i++){
                free_tetromino(sacs[i]);
            }
            free(sacs);
        }
        scores[n-1]=get_score(b);
        free_board(b);
        end=clock();
        temps[n-1]=(double)(end-start)/(double)CLOCKS_PER_SEC;
    }
    printf("le tableau de valeurs:\n");
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