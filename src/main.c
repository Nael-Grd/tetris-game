#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/interface.h"
#include <stddef.h>
#include <stdio.h>


int main() {
    
    /* Initialisation du jeu */
    board my_board = create_board(8,8,4);
    for (int i=0; i<4; i++) {
        add_tetromino_to_bag(my_board, create_random_tetromino());
    }

    /* Boucle du jeu  */
    int end = 0;
    while (end == 0) {
        display_board(my_board);      //on affiche le plateau
        int action = choose_action();
        switch (action) {
            case 0:
                end = 1;
                break;
            case 1:
                tetromino tet1 = select_tetromino_in_bag(my_board);    //selection d'un tetro
                if (tet1 != NULL) {
                    remove_tetromino_from_bag(my_board, tet1);              //on le retire du sac
                    int pr; int pc;
                    ask_place_tetromino(my_board, &pr, &pc, tet1);     //placer le tetro
                    if (check_place_tetromino(my_board, pr, pc, tet1)==1) {
                        place_tetromino(my_board, pr, pc, tet1);
                        add_tetromino_to_bag(my_board, create_random_tetromino());    //si on l'a placé on complete le sac
                        //Tahce E3: ajouter l'option de réserver le tetromino
                        int act; char in[100];
                        int truc=1;
                        while(truc){
                            printf("voulez-vous mettre le tetromino dans la réserve? Oui(1) ou non(2)\n");
                            fgets(in,sizeof(in),stdin);
                            if(sscanf(in,"%d",&act)==1 && (act==1 || act==2)) truc =0;
                            else printf("Entrée invalide. Veuillez saisir 1 ou 2\n");
                        }
                        if(act==1){
                            if(reserve_tetromino(my_board,tet1)==1){
                                printf("bien réservé\n");
                            }
                        }
                    }
                    else {
                        display_message("Lfffgfhfh\n");
                        add_tetromino_to_bag(my_board, tet1);       //sinon on le remet dans le sac
                    }
                }
                break;
            case 2:
                tetromino tet2 = select_tetromino_on_grid(my_board);  //selection d'un tetro sur la grille
                if (tet2 != NULL) {
                    int r; int c;                          //on supprime le tetro du plateau
                    remove_tetromino(my_board, &r, &c, tet2);
                    int pr; int pc;
                    ask_place_tetromino(my_board, &pr, &pc, tet2);     //placer le tetro
                        if (place_tetromino(my_board, pr, pc, tet2) == 1) {
                            break;                        //si on l'a placé fin du tour
                        }
                        else {
                            place_tetromino(my_board, pr, pc, tet2); //sinon on remet le tetro ou il etait       
                        }
                }
                break;
            case 3: //Tâche E3: ajouté l'option de la réserve.
                tetromino tet3=remove_tetromino_from_reserve(my_board);
                printf("récup tet3\n");
                if(tet3!=NULL){
                    int pr;int pc;
                    ask_place_tetromino(my_board,&pr,&pc,tet3);
                    if (place_tetromino(my_board, pr, pc, tet3) == 1) {
                        break;                        //si on l'a placé fin du tour
                    }
                    else {
                        place_tetromino(my_board, pr, pc, tet3); //sinon on remet le tetro ou il etait       
                    }
                }
                break;
            default:
                break;
        }
    }

    /* Fin du jeu */
    display_end_game(my_board);    //fin de jeu
    printf("Score final : %d\n", get_score(my_board));
    free_board(my_board);
    
    return 0;
}