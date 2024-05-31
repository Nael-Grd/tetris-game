#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/interface.h"
#include "../include/constantes.h"
#include <stddef.h>
#include <stdio.h>

/* E.2 */

/*  @requires: b a valid adress of a board, t a valid adress of a tetromino, n a positive integer
    @assigns: modification of the board b because of the movement of tetromino t
    @ensures: If possible, the procedure moves the tetromino t in board b. If not, the procedure leaves the tetromino to its original position.
*/
void gestion_tourner(board b, tetromino t, int n) {
    int pr;
    int pc;
    int row_t;
    int column_t;
    remove_tetromino(&b, &row_t, &column_t, t); //On retire le tetromino de la position à laquelle il était
    ask_turn_tetromino(b, pr, pc, t); //Demande à la joueuse comment tourner le tetromino
    int* tab = calloc(n*n-2, sizeof(int*)); //Allocation d'un tableau qui va permettre de stocker toute les positions qui ont été selectionné et qui sont mauvaise hormis la position dans laquelle il était à l'origine
    int i=0;
    //Gestion du cas où on ne peut pas déplacer le tetromino
    //Soit parce que il n'y a plus aucune place possible en dehors de la place dans laquelle il était et dans ce cas on repositionne le tetromino dans sa position initiale, soit parce que la joueuse a mal choisi
    while(place_tetromino(&b, pr, pc, t)!=0) {
        //Ici les pr et pc ne peuvent pas correspondre à la position que le tetromino avait avant de le déplacer car sinon place_tetromino serait égal à 1
        
        if(i==n*n-2) {
            //Dans le cas où la joueuse a essayé de déplacer le tetromino dans toute les positions possible (en dehors de sa position de base) sans succès
            //On décide finalement de déplacer le tetromino dans la position où il était à l'origine
            pr=row_t;
            pc=column_t;
            continue;
        }

        //On stock petit à petit les positions pour lesquelles la joueuse ne peut pas déplacer le tetromino 
        //jusqu'à arriver au cas ci dessus ou alors jusqu'à que la joueuse trouve une bonne position
        tab[i]=pr;
        tab[i+1]=pc;
        i=i+2;
        for(int j=0; j<i; j+=2) {
            if(pr==tab[j] && pc==tab[j+1]) {
                tab[i-1]=0;
                tab[i-2]=0;
                i=i-2;
                break;
            }
        }
        //A chaque itération on redemande de placer le tetromino en affichant les informations du jeu pour que la joueuse comprenne que la position précédente ne fonctionne pas
        display_board(b);
        ask_turn_tetromino(b, pr, pc, t);
    }
    free(tab);
}



/*  @requires: b a valid adress of a board, t a valid adress of a tetromino, n a positive integer
    @assigns: modification of the board b because of the movement of tetromino t
    @ensures: If possible, the procedure moves the tetromino t in board b. If not, the procedure leaves the tetromino to its original position.
*/
void gestion_tourner_deplacer(board b, tetromino t, int n) {
    int pr;
    int pc;
    int row_t;
    int column_t;
    remove_tetromino(&b, &row_t, &column_t, t); //On retire le tetromino de la position à laquelle il était
    ask_turn_and_deplace_tetromino(b, &pr, &pc, t); //Demande l'endroit où la joueuse souhaite déplacer le tetromino
    int* tab = calloc(n*n-2, sizeof(int*)); //Allocation d'un tableau qui va permettre de stocker toute les positions qui ont été selectionné et qui sont mauvaise hormis la position dans laquelle il était à l'origine
    int i=0;
    //Gestion du cas où on ne peut pas déplacer le tetromino
    //Soit parce que il n'y a plus aucune place possible en dehors de la place dans laquelle il était et dans ce cas on repositionne le tetromino dans sa position initiale, soit parce que la joueuse a mal choisi
    while(place_tetromino(&b, pr, pc, t)!=0) {
        //Ici les pr et pc ne peuvent pas correspondre à la position que le tetromino avait avant de le déplacer car sinon place_tetromino serait égal à 1
        
        if(i==n*n-2) {
            //Dans le cas où la joueuse a essayé de déplacer le tetromino dans toute les positions possible (en dehors de sa position de base) sans succès
            //On décide finalement de déplacer le tetromino dans la position où il était à l'origine
            pr=row_t;
            pc=column_t;
            continue;
        }

        //On stock petit à petit les positions pour lesquelles la joueuse ne peut pas déplacer le tetromino 
        //jusqu'à arriver au cas ci dessus ou alors jusqu'à que la joueuse trouve une bonne position
        tab[i]=pr;
        tab[i+1]=pc;
        i=i+2;
        for(int j=0; j<i; j+=2) {
            if(pr==tab[j] && pc==tab[j+1]) {
                tab[i-1]=0;
                tab[i-2]=0;
                i=i-2;
                break;
            }
        }
        //A chaque itération on redemande de placer le tetromino en affichant les informations du jeu pour que la joueuse comprenne que la position précédente ne fonctionne pas
        display_board(b);
        ask_turn_and_deplace_tetromino(b, &pr, &pc, t);
    }
    free(tab);
}



int main() {
    
    /* Initialisation du jeu */
    board my_board = create_board(8,8,4);
    for (int i=0; i<4; i++) {
        add_tetromino_to_bag(my_board, create_random_tetromino());
    }

    /* Boucle du jeu  */
    int end = 0;
    int vider_reserve=-1;
    int reserve_pleine=0;
    while (end == 0) {
        display_board(my_board);      //on affiche le plateau
truc:
        int action = choose_action();
        switch (action) {
            case 0:
                end = 1;
                break;
            case 1:
                tetromino tet1 = select_tetromino_in_bag(my_board);    //selection d'un tetro
                if (tet1 != NULL) {
                    remove_tetromino_from_bag(my_board, tet1);              //on le retire du sac
                    
                    display_tetromino(tet1);
                    int pr; int pc;
                    ask_place_tetromino(my_board, &pr, &pc, tet1);     //placer le tetro
                    if (check_place_tetromino(my_board, pr, pc, tet1)==1) {
                        place_tetromino(my_board, pr, pc, tet1);
                        if(vider_reserve!=-1)vider_reserve++;
                        if(vider_reserve==2){
                            free_tetromino(list_reserve(my_board));
                            vider_reserve=-1;
                            remove_tetromino_from_reserve(my_board);
                        }
                        add_tetromino_to_bag(my_board, create_random_tetromino());    //si on l'a placé on complete le sac
                        //Tahce E3: ajouter l'option de réserver le tetromino
                        if(!reserve_pleine){
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
                                    vider_reserve=0;
                                    reserve_pleine=1;
                                }
                            }
                        }
                    }
                    else {
                        display_message("tetromino pas placé\n");
                        add_tetromino_to_bag(my_board, tet1);       //sinon on le remet dans le sac
                    }
                }
                break;
            case 2:
                tetromino tet2 = select_tetromino_on_grid(my_board);  //selection d'un tetro sur la grille
                gestion_placement(my_board, tet1, n);
                
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
                tetromino tet3=list_reserve(my_board);
                if(tet3!=NULL){
                    display_tetromino(tet3);
                    int pr;int pc;
                    ask_place_tetromino(my_board,&pr,&pc,tet3);
                    if (place_tetromino(my_board, pr, pc, tet3) == 1) {
                        remove_tetromino_from_reserve(my_board);
                        reserve_pleine=0;
                        vider_reserve=-1;
                        break;                        //si on l'a placé fin du tour
                    }
                    else {
                        place_tetromino(my_board, pr, pc, tet3); //sinon on remet le tetro ou il etait       
                    }
                }
                else{
                    printf("la réserve est vide!!\n");
                    goto truc;
                }
                break;

                /* E.2 */

                    tetromino t = select_tetromino_on_grid(b); //Sélection du tetromino que la joueuse souhaite déplacer
        gestion_placement(my_board, tet1, n);
                    //Apres gestion_deplacement, soit le tetromino a été deplacé soit il est resté à la meme position si aucun déplacement n'est possible
                    display_board(b);
                
            case 4 :     
                
                    tetromino t = select_tetromino_on_grid(b); //Sélection du tetromino que la joueuse souhaite déplacer
        gestion_placement(my_board, tet1, n);
                    //Apres gestion_deplacement, soit le tetromino a été deplacé soit il est resté à la meme position si aucun déplacement n'est possible
                    display_board(my_board);
                
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
