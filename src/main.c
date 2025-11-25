#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/interface.h"
#include "../include/carte.h"
#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdio.h>

/**
 * @brief Initialise le jeu avec un plateau et un sac de tétriminos.
 * 
 * @param n Le nombre de lignes et de colonnes du plateau.
 * @param k Le nombre de tétriminos dans le sac.
 * @return Le plateau de jeu initialisé.
 */
board init_jeu(int n, int k) {
    board b = create_board(n, n, k);
    for (int i = 0; i < 4; i++) {
        tetromino t_init = create_random_tetromino();
        add_tetromino_to_bag(b, t_init);  // Corrigé: pas &b
    }
    return b;
}

/**
 * @brief Gère le placement d'un tétrimino sur le plateau.
 * 
 * @param b Le plateau.
 * @param t Le tétrimino.
 * @param etat L'état actuel du jeu.
 */
void gestion_placement(board b, tetromino t, int etat) {
    int row;
    int col;
    ask_rotate_tetromino(t);  // Corrigé: ask_rotate_tetromino au lieu de ask_turn_tetromino
    ask_place_tetromino(b, &row, &col, t);
    place_tetromino(b, row, col, t);  // Corrigé: pas &b
}

/**
 * @brief Gère le sac après un mouvement de tétrimino sur le plateau.
 * 
 * @param b Le plateau.
 * @param t Le tétrimino.
 */
void gestion_du_sac_apres_mouvement(board b, tetromino t) {
    remove_tetromino_from_bag(b, t);  // Corrigé: pas &b
    tetromino new_tetromino = create_random_tetromino();
    add_tetromino_to_bag(b, new_tetromino);  // Corrigé: pas &b
}

/**
 * @brief Fonction principale qui lance le jeu.
 * 
 * @return 0 si le jeu se termine correctement.
 */
int main() {
    srand(time(NULL));
    
    // Initialisation du temps CPU
    clock_t start_time, end_time;
    double cpu_time;
    start_time = clock();
    
    /* Initialisation du jeu */
    board my_board = create_board(8, 8, 4);
    for (int i = 0; i < 4; i++) {
        add_tetromino_to_bag(my_board, create_random_tetromino());
    }

    int end = 0;
    int vider_reserve = -1;
    int reserve_pleine = 0;
    
    while (end == 0) {
        display_board(my_board);      // on affiche le plateau
        
truc:
        int action = choose_action();
        switch (action) {
            case 0:
                end = 1;
                break;
                
            case 1:
                {
                    tetromino tet1 = select_tetromino_in_bag(my_board);    // selection d'un tetro
                    ask_use_carte(my_board);  // Corrigé: pas &my_board
                    
                    if (tet1 != NULL) {
                        remove_tetromino_from_bag(my_board, tet1);              // on le retire du sac
                        ask_rotate_tetromino(tet1);
                        display_tetromino(tet1);
                        int pr; int pc;
                        ask_place_tetromino(my_board, &pr, &pc, tet1);     // placer le tetro
                        
                        if (check_place_tetromino(my_board, pr, pc, tet1) == 1) {
                            place_tetromino(my_board, pr, pc, tet1);
                            if (vider_reserve != -1) vider_reserve++;
                            if (vider_reserve == 2) {
                                free_tetromino(list_reserve(my_board));
                                vider_reserve = -1;
                                remove_tetromino_from_reserve(my_board);
                            }
                            
                            // Temporairement désactivé - fonctions manquantes
                            /*
                            carte card = get_carte(my_board, tet1);
                            ask_use_carte(&my_board);
                            
                            if (card != NULL) {
                                add_carte(&my_board, card);
                            }
                            */
                            
                            add_tetromino_to_bag(my_board, create_random_tetromino());    // si on l'a placé on complete le sac
                            
                            // Tache E3: ajouter l'option de réserver le tetromino
                            if (!reserve_pleine) {
                                int act; char in[100];
                                int truc = 1;
                                while (truc) {
                                    printf("voulez-vous mettre le tetromino dans la réserve? Oui(1) ou non(2)\n");
                                    fgets(in, sizeof(in), stdin);
                                    if (sscanf(in, "%d", &act) == 1 && (act == 1 || act == 2)) truc = 0;
                                    else printf("Entrée invalide. Veuillez saisir 1 ou 2\n");
                                }
                                if (act == 1) {
                                    if (reserve_tetromino(my_board, tet1) == 1) {
                                        printf("bien réservé\n");
                                        vider_reserve = 0;
                                        reserve_pleine = 1;
                                    }
                                }
                            }
                        } else {
                            display_message("tetromino pas placé\n");
                            add_tetromino_to_bag(my_board, tet1);       // sinon on le remet dans le sac
                        }
                    }
                }
                break;
                
            case 2:
                {
                    tetromino tet2 = select_tetromino_on_grid(my_board);  // selection d'un tetro sur la grille
                    if (tet2 != NULL) {
                        int r; int c;                          // on supprime le tetro du plateau
                        remove_tetromino(my_board, &r, &c, tet2);
                        int pr; int pc;
                        ask_place_tetromino(my_board, &pr, &pc, tet2);     // placer le tetro
                        if (place_tetromino(my_board, pr, pc, tet2) == 1) {
                            break;                        // si on l'a placé fin du tour
                        } else {
                            place_tetromino(my_board, r, c, tet2); // sinon on remet le tetro ou il etait       
                        }
                    }
                }
                break;
                
            case 3: // Tâche E3: ajouté l'option de la réserve.
                {
                    tetromino tet3 = list_reserve(my_board);
                    printf("récup tet3\n");
                    if (tet3 != NULL) {
                        ask_rotate_tetromino(tet3);
                        display_tetromino(tet3);
                        int pr; int pc;
                        ask_place_tetromino(my_board, &pr, &pc, tet3);
                        if (place_tetromino(my_board, pr, pc, tet3) == 1) {
                            remove_tetromino_from_reserve(my_board);
                            reserve_pleine = 0;
                            vider_reserve = -1;
                            break;                        // si on l'a placé fin du tour
                        } else {
                            // Ne pas replacer ici, juste continuer
                        }
                    } else {
                        printf("la réserve est vide!!\n");
                        goto truc;
                    }
                }
                break;
                
            default:
                break;
        }
        
        // Temporairement désactivé - fonction manquante
        // if (tetrominos_placeables(my_board) == 0) end = 1;
    }

    /* Fin du jeu */
    display_end_game(my_board);    // fin de jeu
    printf("Score final : %d\n", get_score(my_board));
    free_board(my_board);

    end_time = clock();
    cpu_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Temps CPU utilisé : %f secondes\n", cpu_time);
    
    return 0;
}