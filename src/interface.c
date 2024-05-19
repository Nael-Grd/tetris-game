#include "../include/interface.h"
#include "../include/board.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../include/carte.h"


// Fonction pour choisir l'action
int choose_action() {
    // Affiche le message donné en entrée
    printf("%s\n", message);
}


/*Début de l'adaptation d'interface.c  de la Tache E4 faite par "ALI DAOUDI" */

/**
 * @brief Displays the details of a special card.
 *
 * @param cte The special card to display.
 */
void show_card(carte cte) {
    printf("\n\n << Card Name: %s \n    Description: %s >>\n\n", get_name_card(cte), get_info_carte(cte));
}

/**
 * @brief Applies the necessary effect when a card is used.
 *
 * @param b The game board.
 * @param c The index of the card to use.
 */
void to_need_to_use_card(board* b, int c) {
    carte* list_cte = get_list_card(*b);
    if (!list_cte[c]) return;
    
    int n = get_num(list_cte[c]);
    switch (n) {
        case 0:
            printf("Select the tetromino you want to remove\n");
            use_card(list_cte[c], b, -1, NULL);
            break;
        case 1:
        case 2:
            if (reserve_is_empty(*b)) {
                printf("\n Card without effect, empty reservoir! \n");
            } else {
                use_card(list_cte[c], b, n, NULL);
            }
            break;
        case 3:
            printf("\n<< Select tetrominos to remove, as many as you want >>\n\n");
            while (tetromino_in_board(*b)) {
                tetromino tr = select_tetromino_on_grid(*b);
                if (!tr) break;
                add_to_score(b, -1);
                use_card(list_cte[c], b, -1, tr);
            }
            if (!tetromino_in_board(*b)) printf("Empty board, cannot remove another tetromino\n");
            break;
        case 5:
            if (reserve_is_empty(*b)) {
                printf("\n Card without effect, empty reservoir! \n");
            } else {
                printf("Select the tetromino you want to exchange:\n");
                tetromino* sac = list_tetrominos_in_bag(*b);
                if (!sac) break;
                int c;
                scanf("%d", &c);
                if (c < 1 || c > 4) break;
                use_card(list_cte[c], b, -1, sac[c-1]);
            }
            break;
        case 6:
            if (reserve_is_full(*b)) {
                printf("\n Card without effect, full reservoir! \n");
            } else {
                use_card(list_cte[c], b, n, NULL);
            }
            break;
        case 7:
            printf("\n<< Select up to 3 tetrominos to remove while the board is not empty >>\n\n");
            for (int i = 0; i < 3 && tetromino_in_board(*b); i++) {
                tetromino tr = select_tetromino_on_grid(*b);
                if (!tr) break;
                add_to_score(b, get_nb_points(tr));
                use_card(list_cte[c], b, -1, tr);
            }
            break;
        case 8:
        case 16:
            use_card(list_cte[c], b, -1, NULL);
            break;
        case 14:
            printf("<< Select a tetromino (number) >>\n");
            int t;
            scanf("%d", &t);
            if (t >= 1 && t <= (*b)->k) {
                use_card(list_cte[c], b, t - 1, NULL);
            }
            break;
        case 17:
            printf("<< Expanding your bag by +1 >> \n");
            use_card(list_cte[c], b, -1, NULL);
            break;
        default:
            break;
    }
    remove_card(b, get_num(list_cte[c]));
}

/**
 * @brief Prompts the user to use a special card.
 *
 * @param b The game board.
 */
void ask_use_card(board* b) {
    carte* list_cte = get_list_card(*b);
    if (!list_cte) return;
    
    printf("\nDo you want to use a special card? \n");
    printf("0: No / 1: Yes \n");
    int c;
    printf("\nEnter your choice: ");
    scanf("%d", &c);
    
    bool has_card = false;
    for (int i = 0; i < 8; i++) {
        if (list_cte[i]) {
            has_card = true;
            break;
        }
    }
    
    if (c == 1 && has_card) {
        printf("\n<< List of available cards >>\n\n");
        for (int i = 0; i < 8; i++) {
            if (list_cte[i]) {
                printf("Special card no.: %d", i);
                show_card(list_cte[i]);
            }
        }
        printf("Enter the card number you want to use:\n");
        scanf("%d", &c);
        if (c >= 0 && c < 8) {
            to_need_to_use_card(b, c);
        }
    } else if (!has_card) {
        printf("\nUnable to choose a special card, you have none!\n\n");
    }
}
/*FIN de la Partie d'adaptation de la Tache:E4 pour interface .c faite par "ALI DAOUDI"*/
