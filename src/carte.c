#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/carte.h"

// Defining the structure for a card, which contains a number, a name, and a description.
struct s_carte {
    int num;
    char* name;
    char* description;
};

carte create_carte() {
    // Initialize random number generator
    srand(time(NULL));

    // Generate a random number between 0 and 17, excluding specific numbers
    int num;
    do {
        num = rand() % 18;
<<<<<<< HEAD
    } while (num == 4 || num == 9 || num == 10 || num == 11 || num == 12 || num == 13 || num == 15);
=======
        is_excluded = 0;
        for (int i = 0; i < excluded_size; i++) {
            if (num == excluded[i]) {
                is_excluded = 1;
                break;
            }
        }
    } while (is_excluded);
    return num;
}

/**
 * @brief Crée une nouvelle carte avec des attributs aléatoires.
 * 
 * @return carte Pointeur vers la nouvelle carte créée.
 */
carte create_carte() {
    int excluded_nums[] = {3,4,6,7,9,10,11,12,13,14,15,16,17};
    int excluded_size = sizeof(excluded_nums) / sizeof(excluded_nums[0]);
    int num = generate_random_num_excluding(excluded_nums, excluded_size);
>>>>>>> 63faeef75d99873448f1cdd402e62befa0e83091

    // Allocate memory for the new card
    carte cte = malloc(sizeof(struct s_carte));
    if (cte == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the card based on the random number
    switch (num) {
        case 0:
            cte->num = 0;
            cte->name = "Thuy Vo";
            cte->description = "Supprimez une pièce du sac, elle est remplacée par une autre pièce aléatoirement.";
            break;
        case 1:
            cte->num = 1;
            cte->name = "David Roussel";
            cte->description = "Supprimez une pièce dans la réserve. La carte n'a pas d'effet si la réserve est vide.";
            break;
        case 2:
            cte->num = 2;
            cte->name = "Abass Sagna";
            cte->description = "Remplacez la pièce de réserve par un nouveau tétromino choisi aléatoirement. La carte n'a pas d'effet si la réserve est vide.";
            break;
        case 3:
            cte->num = 3;
            cte->name = "Renaud Rioboo";
            cte->description = "Choisissez autant de pièces que vous souhaitez sur le plateau. Ces pièces sont supprimées. Pour chaque pièce supprimée, vous perdez un point plus le nombre de points associés à la pièce.";
            break;
        case 5:
            cte->num = 5;
            cte->name = "Laurence Bourard";
            cte->description = "Choisissez une pièce du sac et une pièce de la réserve et échangez-les. La carte n'a pas d'effet si la réserve est vide.";
            break;
        case 6:
            cte->num = 6;
            cte->name = "Massinissa Merabet";
            cte->description = "Choisissez une pièce du plateau, ajoutez une nouvelle pièce identique dans la réserve. Cette carte n'a pas d'effet si la réserve est pleine.";
            break;
        case 7:
            cte->num = 7;
            cte->name = "Anne-Laure Ligozat";
            cte->description = "Supprimez 3 pièces du plateau. Vous ne perdez aucun point.";
            break;
        case 8:
            cte->num = 8;
            cte->name = "Christophe Mouilleron";
            cte->description = "Remplacez les 4 pièces du sac par 4 nouvelles pièces aléatoires.";
            break;
        case 14:
            cte->num = 14;
            cte->name = "Cyril Benezet";
            cte->description = "Choisissez un tétromino (n'importe lequel, pas forcément une pièce en jeu), remplacez toutes les pièces du sac par cette pièce.";
            break;
        case 16:
            cte->num = 16;
            cte->name = "Dimitri Watel";
            cte->description = "La réserve peut contenir une pièce de plus jusqu'à la fin de la partie.";
            break;
        case 17:
            cte->num = 17;
            cte->name = "Marie Szafranski";
            cte->description = "Votre sac peut maintenant contenir une pièce de plus. Une nouvelle pièce choisie aléatoirement est ajoutée à votre sac.";
            break;
        default:
            free(cte);
            fprintf(stderr, "Unexpected card number: %d\n", num);
            exit(EXIT_FAILURE);
    }
    return cte;
}

int get_num(carte cte) {
    return cte->num;
}

char* get_name_card(carte cte) {
    return cte->name;
}

char* get_info_carte(carte cte) {
    return cte->description;
}

void free_card(carte cte) {
    free(cte);
}

