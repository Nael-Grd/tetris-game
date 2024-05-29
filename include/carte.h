#ifndef CARTE_H
#define CARTE_H

/**
 * @brief Structure représentant une carte.
 */
typedef struct s_carte* carte;

/**
 * @brief Crée une nouvelle carte avec des attributs aléatoires.
 * 
 * @return carte Pointeur vers la nouvelle carte créée.
 */
carte create_carte(void);

/**
 * @brief Récupère le numéro d'une carte.
 * 
 * @param cte La carte dont on veut obtenir le numéro.
 * @return int Le numéro de la carte.
 */
int get_num(carte cte);

/**
 * @brief Récupère le nom d'une carte.
 * 
 * @param cte La carte dont on veut obtenir le nom.
 * @return char* Le nom de la carte.
 */
char* get_name_card(carte cte);

/**
 * @brief Récupère la description d'une carte.
 * 
 * @param cte La carte dont on veut obtenir la description.
 * @return char* La description de la carte.
 */
char* get_info_carte(carte cte);

/**
 * @brief Libère la mémoire allouée pour une carte.
 * 
 * @param cte La carte à libérer.
 */
void free_card(carte cte);

#endif /* CARTE_H */
