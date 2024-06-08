#ifndef __CART_H_
#define __CART_H_

/**
 * @brief A structure representing a card.
 */
typedef struct s_carte* carte;

/**
 * @brief Creates a new card randomly.
 *
 * @return A new card.
 * @pre A non-null card must be created.
 * @post A new card is created randomly.
 */
carte create_carte();

/**
 * @brief Gets the card's number.
 *
 * @param cte A non-null card.
 * @return The card's number.
 * @pre The card must be non-null.
 * @post Returns the card's number.
 */
int get_num(carte cte);

/**
 * @brief Gets the card's name.
 *
 * @param cte A non-null card.
 * @return The card's name.
 * @pre The card must be non-null.
 * @post Returns the card's name.
 */
char* get_name_card(carte cte);

/**
 * @brief Retrieves the card's description or name.
 *
 * @param cte A non-null card.
 * @return The card's description or name.
 * @pre The card must be non-null.
 * @post Returns the card's description or name.
 */
char* get_info_carte(carte cte);

/**
 * @brief Frees the card.
 *
 * @param cte A valid card address.
 * @pre The card address must be valid.
 * @post Frees the memory allocated to the card.
 */
void free_card(carte cte);

<<<<<<< HEAD
#endif
=======
#endif /* CARTE_H */

>>>>>>> 63faeef75d99873448f1cdd402e62befa0e83091
