#include <stdio.h>
#include <stdlib.h>
#include "../include/carte.h"


/**
 * @struct s_carte
 * @brief Structure représentant une carte.
 */
struct s_carte {
    int num;           /**< Numéro de la carte */
    char* name;        /**< Nom de la carte */
    char* description; /**< Description de la carte */
};

/**
 * @brief Génère un nombre aléatoire excluant certains numéros.
 * 
 * @param excluded Tableau des numéros à exclure.
 * @param excluded_size Taille du tableau des numéros à exclure.
 * @return int Nombre aléatoire généré qui n'est pas dans le tableau des exclus.
 */
int generate_random_num_excluding(int excluded[], int excluded_size) {
    int num;
    int is_excluded;
    do {
        num = rand() % 18;
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
    int excluded_nums[] = {4, 9, 10, 11, 12, 13, 15};
    int excluded_size = sizeof(excluded_nums) / sizeof(excluded_nums[0]);
    int num = generate_random_num_excluding(excluded_nums, excluded_size);

    carte cte = malloc(sizeof(struct s_carte));
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
            cte->description = "Choisissez une pièce du sac et une pièce de la réserve et échangez les. La carte n'a pas d'effet si la réserve est vide.";
            break;
        case 6:
            cte->num = 6;
            cte->name = "Massinissa Merabet";
            cte->description = "Choisissez une pièce du plateau, ajoutez une nouvelle pièce identique dans la réserve. Cette carte n'a pas d'effet si la réserve est pleine.";
            break;
        case 7:
            cte->num = 7;
            cte->name = "Anne-Laure Ligozat";
            cte->description = "Supprimez 3 pièces du plateau. Vous ne perdez aucun points.";
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
    }
    return cte;
}

/**
 * @brief Récupère le numéro d'une carte.
 * 
 * @param cte La carte dont on veut obtenir le numéro.
 * @return int Le numéro de la carte.
 */
int get_num(carte cte) {
    return cte->num;
}

/**
 * @brief Récupère le nom d'une carte.
 * 
 * @param cte La carte dont on veut obtenir le nom.
 * @return char* Le nom de la carte.
 */
char* get_name_card(carte cte) {
    return cte->name;
}

/**
 * @brief Récupère la description d'une carte.
 * 
 * @param cte La carte dont on veut obtenir la description.
 * @return char* La description de la carte.
 */
char* get_info_carte(carte cte) {
    return cte->description;
}

/**
 * @brief Libère la mémoire allouée pour une carte.
 * 
 * @param cte La carte à libérer.
 */
void free_card(carte cte) {
    free(cte);
}
