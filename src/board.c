#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/carte.h"

#define MEMORY_ERROR 1
#define INVALID_PARAMETERS_ERROR 2
#define PLACEMENT_POSSIBLE 1
#define PLACEMENT_IMPOSSIBLE 0

// Structure pour représenter le plateau de jeu
struct BoardStruct
{
    int nbLignes;    // Nombre de lignes du plateau
    int nbColonnes;  // Nombre de colonnes du plateau
    int tailleSac;   // Taille du sac de tétromino
    tetromino *bd;   // Copie de tetromino dans le board
    tetromino reserve[1]; //lot E.3: sac de tétrominos réservés
    tetromino *sac;  // Sac de tétromino
    int **grille;    // Grille du plateau de jeu
    int scoreActuel; // Score actuel
     carte* list_of_cards; // liste des cartes spéciales
};

/**
 * Fonction `create_board`
 * @param nbLignes Le nombre de lignes du plateau.
 * @param nbColonnes Le nombre de colonnes du plateau.
 * @param tailleSac La taille initiale du sac de tetrominos.
 * @return Le plateau de jeu nouvellement créé.
 */
board create_board(int nbLignes, int nbColonnes, int tailleSac)
{
    if (nbLignes <= 0 || nbColonnes <= 0 || tailleSac <= 0)
    {
        fprintf(stderr, "Erreur : paramètres invalides.\n");
        exit(INVALID_PARAMETERS_ERROR);
    }

    board newBoard = malloc(sizeof(struct BoardStruct));
    if (newBoard == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(MEMORY_ERROR);
    }

    // Initialiser les membres de la structure selon les paramètres
    newBoard->nbLignes = nbLignes;
    newBoard->nbColonnes = nbColonnes;
    newBoard->tailleSac = tailleSac;
    newBoard->scoreActuel = 0;

    // Allouer la mémoire pour le sac de tétromino
    newBoard->sac = malloc(tailleSac * sizeof(tetromino));
    if (newBoard->sac == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(MEMORY_ERROR);
    }

    newBoard->bd = malloc(nbColonnes * nbLignes * sizeof(tetromino));
    if (newBoard->bd == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(MEMORY_ERROR);
    }
    // Initialiser la copie bd à NULL
    for (int i = 0; i < tailleSac; i++)
    {
        newBoard->bd[i] = NULL;
    }

    // Allouer et initialiser la mémoire pour la grille du plateau de jeu
    newBoard->grille = calloc(nbLignes, sizeof(int *));
    if (newBoard->grille == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(MEMORY_ERROR);
    }
    for (int i = 0; i < nbLignes; i++)
    {
        newBoard->grille[i] = calloc(nbColonnes, sizeof(int));
        if (newBoard->grille[i] == NULL)
        {
            fprintf(stderr, "Erreur d'allocation mémoire.\n");
            exit(MEMORY_ERROR);
        }
    }
    /* Ajout de ALi DAOUDI pour Tache E.4 dans la mesure de creer de la memoire pour la listes_des_cartes   */
    
    b->list_of_cards = malloc(8*sizeof(carte));     /* Ajout de ALi DAOUDI pour Tache E.4 dans la mesure de creer de la memoire pour la listes_des_cartes   */


    return newBoard;
}

/**
 * Fonction `free_board`
 * @param b Le plateau de jeu à libérer.
 */

void free_board(board b)
{
    if (b == NULL)
    {
        return; // Si le pointeur est NULL, il n'y a rien à libérer
    }

    for (int i = 0; i < b->tailleSac; i++)
    {
        free_tetromino(b->bd[i]);
    }
    free(b->bd);

    // Libérer la mémoire allouée pour le sac de tetrominos
    for (int i = 0; i < b->tailleSac; i++)
    {
        free_tetromino(b->sac[i]); // appelle la fonction free_tetromino
    }
    free(b->sac);
    // Libérer la mémoire allouée pour chaque ligne de la grille
    for (int i = 0; i < b->nbLignes; i++)
    {
        free(b->grille[i]);
    }
    // Libérer la mémoire allouée pour la grille
    free(b->grille);
    // Libérer la mémoire allouée pour la structure BoardStruct
    free((*b)->list_of_cards);
    free(b);
}


/* start : the TACHE:E4 done by ALI DAOUDI  to implemente somme functions to use cards   */

/**
 * @brief Checks if the reserve is full.
 * 
 * @param b The board structure.
 * @return true if the reserve is full, false otherwise.
 */
bool reserve_is_full(board b) {
    int i = 0;
    for (int i = 0; i < b->r; i++) {
        if (b->reserve[i] != NULL) {
            i++;
        }
    }
    if (i == b->r) {
        return true;
    }
    return false;
}

/**
 * @brief Displays the contents of the reserve.
 * 
 * @param b The board structure.
 */
void show_reserve(board b) {
    printf("\n\nDans la reserve il y a :\n");
    for (int i = 0; i < b->r; i++) {
        printf("Tetromino %d : id: %d, type: %d, points: %d\n\n", i + 1, get_id(b->reserve[i]), get_type(b->reserve[i]), get_nb_points(b->reserve[i]));
    }
}

/**
 * @brief Adds an amount to the board's score.
 * 
 * @param b A pointer to the board structure.
 * @param amount The amount to add to the score.
 */
void add_to_score(board* b, int amount) {
    (*b)->score += amount;
}

/**
 * @brief Gets the size of the bag.
 * 
 * @param b The board structure.
 * @return The size of the bag.
 */
int get_size_bag(board b) {
    return b->k;
}

/**
 * @brief Gets the size of the reserve.
 * 
 * @param b The board structure.
 * @return The size of the reserve.
 */
int get_size_reserve(board b) {
    return b->r;
}

/**
 * @brief Checks if a tetromino is present on the board.
 * 
 * @param b The board structure.
 * @param t The tetromino to check.
 * @return true if the tetromino is present, false otherwise.
 */
bool is_card(board b, tetromino t) {
    int spec_case[8] = {7, 1, 5, 3, 4, 2, 6, 0};
    for (int i = 0; i < 8; i++) {
        tetromino tetro = get_tetromino(b, i, spec_case[i]);
        if (tetro != NULL && get_id(tetro) == get_id(t)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets a card associated with a tetromino.
 * 
 * @param b The board structure.
 * @param t The tetromino.
 * @return The card if the tetromino is a card, otherwise NULL.
 */
carte get_card(board b, tetromino t) {
    if (is_card(b, t) == true) {
        return create_carte();
    }
    return NULL;
}

/**
 * @brief Removes a card from the board's list of cards.
 * 
 * @param b A pointer to the board structure.
 * @param num The number of the card to remove.
 */
void remove_card(board* b, int num) {
    int i = 0;
    while ((*b)->list_of_cards[i] != NULL && i < 8) {
        if (get_num((*b)->list_of_cards[i]) == num) {
            (*b)->list_of_cards[i] = NULL;
            break;
        }
        i++;
    }
}

/**
 * @brief Adds a card to the board's list of cards.
 * 
 * @param b A pointer to the board structure.
 * @param cte The card to add.
 */
void add_card(board* b, carte cte) {
    int i = 0;
    while ((*b)->list_of_cards[i] != NULL) {
        i++;
    }
    (*b)->list_of_cards[i] = cte;
}

/**
 * @brief Applies the effect of the Thuy Vo card.
 * 
 * @param b A pointer to the board structure.
 */
effect Thuy_Vo(board* b) {
    int n;
    scanf("%d", &n);
    remove_tetromino_from_bag(b, (*b)->bag[n-1]);
    add_tetromino_to_bag(b, create_random_tetromino());
}

/**
 * @brief Applies the effect of the David Roussel card.
 * 
 * @param b A pointer to the board structure.
 */
effect David_Roussel(board* b) {
    if (!reserve_is_empty(*b)) {
        remove_from_reserve(b);
    }
}

/**
 * @brief Applies the effect of the Abass Sagna card.
 * 
 * @param b A pointer to the board structure.
 */
effect Abass_Sagna(board* b) {
    if (!reserve_is_empty(*b)) {
        remove_from_reserve(b);
        add_tetromino_in_reserve(b, create_random_tetromino());
    }
    show_reserve(*b);
}

/**
 * @brief Applies the effect of the Renaud Rioboo card.
 * 
 * @param b A pointer to the board structure.
 * @param tr The tetromino to remove.
 */
effect Renaud_Rioboo(board* b, tetromino tr) {
    int p;
    int c;
    remove_tetromino(b, &p, &c, tr);
    display_board(*b);
}

/**
 * @brief Applies the effect of the Laurence Bourard card.
 * 
 * @param b A pointer to the board structure.
 * @param t The tetromino to exchange with the reserve.
 */
effect Laurence_Bourard(board* b, tetromino t) {
    remove_tetromino_from_bag(b, t);
    tetromino tetro_res = get_tetromino_from_reserve(*b);
    remove_from_reserve(b);
    add_tetromino_in_reserve(b, t);
    add_tetromino_to_bag(b, tetro_res);
    show_reserve(*b);
}

/**
 * @brief Applies the effect of the Massinissa Merabet card.
 * 
 * @param b A pointer to the board structure.
 */
effect Massinissa_Merabet(board* b) {
    tetromino tr = select_tetromino_on_grid(*b);
    add_tetromino_in_reserve(b, tr);
    show_reserve(*b);
}

/**
 * @brief Applies the effect of the Anne Laure Ligozat card.
 * 
 * @param b A pointer to the board structure.
 * @param tr The tetromino to remove.
 */
effect Anne_Laure_Ligozat(board* b, tetromino tr) {
    int p;
    int c;
    remove_tetromino(b, &p, &c, tr);
    display_board(*b);
}

/**
 * @brief Applies the effect of the Christophe Mouilleron card.
 * 
 * @param b A pointer to the board structure.
 */
effect Christophe_Mouilleron(board *b) {
    for (int i = 0; i < (*b)->k; i++) {
        remove_tetromino_from_bag(b, (*b)->bag[i]);
        add_tetromino_to_bag(b, create_random_tetromino());
    }
}

/**
 * @brief Applies the effect of the Cyril Benezet card.
 * 
 * @param b A pointer to the board structure.
 * @param n The index of the tetromino to change.
 */
effect Cyril_Benezet(board* b, int n) {
    int type = get_type((*b)->bag[n-1]);
    for (int i = 0; i < (*b)->k; i++) {
        remove_tetromino_from_bag(b, (*b)->bag[i]);
        add_tetromino_to_bag(b, create_tetromino(type, rand(), rand() % 3 + 1));
    }
}

/**
 * @brief Applies the effect of the Dimitri Watel card.
 * 
 * @param b A pointer to the board structure.
 */
effect Dimitri_Watel(board* b) {
    (*b)->r = (*b)->r + 1;
    (*b)->reserve = realloc((*b)->reserve, (*b)->r * sizeof(tetromino));
    show_reserve(*b);
}

/**
 * @brief Applies the effect of the Marie Szafranski card.
 * 
 * @param b A pointer to the board structure.
 */
effect Marie_Szafranski(board* b) {
    (*b)->k = (*b)->k + 1;
    (*b)->bag = realloc((*b)->bag, (*b)->k * sizeof(tetromino));
    (*b)->bag[(*b)->k - 1] = create_random_tetromino();
}

/**
 * @brief Uses a card on the board.
 * 
 * @param cte The card to use.
 * @param b A pointer to the board structure.
 * @param n An integer parameter for certain card effects.
 * @param tr A tetromino parameter for certain card effects.
 */
void use_card(carte cte, board* b, int n, tetromino tr) {
    int numero = get_num(cte);
    switch (numero) {
        case 0: Thuy_Vo(b); break;
        case 1: David_Roussel(b); break;
        case 2: Abass_Sagna(b); break;
        case 3: Renaud_Rioboo(b, tr); break;
        case 5: Laurence_Bourard(b, tr); break;
        case 6: Massinissa_Merabet(b); break;
        case 7: Anne_Laure_Ligozat(b, tr); break;
        case 8: Christophe_Mouilleron(b); break;
        case 14: Cyril_Benezet(b, n); break;
        case 16: Dimitri_Watel(b); break;
        case 17: Marie_Szafranski(b); break;
    }
}

/**
 * @brief Gets the list of cards on the board.
 * 
 * @param b The board structure.
 * @return An array of cards.
 */
carte* get_list_of_card(board b) {
    return b->list_of_cards;
}


/* END of  TACHE:E4  done by ALI DAOUDI to implimente somme card effects */

/**
 * Fonction `list_tetrominos_in_bag`
 * @param b Le plateau de jeu contenant le sac de tétromino.
 * @return Un pointeur vers le sac de tétromino, ou NULL si le plateau est NULL.
 */

tetromino *list_tetrominos_in_bag(board b)
{
    if (b == NULL)
    {
        fprintf(stderr, "Erreur : Le plateau de jeu est NULL.\n");
        return NULL;
    }
    return b->sac;
}

/**
 * Fonction `add_tetromino_to_bag`
 * @param b Le plateau de jeu dans lequel ajouter le tétromino au sac.
 * @param t Le tétromino à ajouter au sac.
 */

void add_tetromino_to_bag(board b, tetromino t)
{
    for (int i = 0; i < b->tailleSac; i++)
    {
        if (b->sac[i] == NULL)
        {
            b->sac[i] = t;
            break;
        }
    }
}

/**
 * Fonction `remove_tetromino_from_bag`
 * @param b Le plateau de jeu dans lequel retirer le tétromino du sac.
 * @param t Le tétromino à retirer du sac.
 */
void remove_tetromino_from_bag(board b, tetromino t)
{
    for (int i = 0; i < b->tailleSac; i++)
    {
        if (get_id(b->sac[i]) == get_id(t)) // L'Id doit etre unique
        {
            b->sac[i] = NULL;
        }
    }
}

/**
 * Fonction `check_place_tetromino`
 * @param b Le plateau de jeu sur lequel vérifier la possibilité de placer le tétromino.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétromino à placer.
 * @return 1 si le tétromino peut être placé, 0 sinon.
 */
int check_place_tetromino(board b, int r, int c, tetromino t)
{
    int *cells = get_cells(t);
    // Vérifier si le tétromino peut être placé
    for (int i = 0; i < 4; i++)
    {
        if (r + cells[2 * i] >= b->nbLignes || c + cells[2 * i + 1] >= b->nbColonnes || r + cells[2 * i] < 0 || c + cells[2 * i + 1] < 0)
        {
            return PLACEMENT_IMPOSSIBLE;
        }
        if ((b->grille[r + cells[2 * i]][c + cells[2 * i + 1]]) != 0)
        {
            return PLACEMENT_IMPOSSIBLE;
        }
    }
    return PLACEMENT_POSSIBLE;
}

/**
 * Fonction `place_tetromino`
 * @param b Le plateau de jeu sur lequel placer le tétromino.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétromino à placer.
 * @return 1 si le tétromino a été placé avec succès, 0 sinon.
 */

int place_tetromino(board b, int r, int c, tetromino t)
{
    if (check_place_tetromino(b, r, c, t))
    {
        int *cells = get_cells(t);
        int nb_points = get_nb_points(t);
        for (int i = 0; i < 8; i += 2)
        {
            b->grille[r + cells[i]][c + cells[i + 1]] = get_id(t); // Utiliser l'ID du tetrominos pour marquer sa présence
        }
        b->scoreActuel += nb_points;

        for (int j = 0; j < b->nbLignes * b->nbColonnes; j++)
        {
            if (b->bd[j] == NULL)
            {
                b->bd[j] = t; // Ajout de tetromino dans bd $
                break;
            }
        }
        return 1; // tétromino placé avec succès
    }
    return 0; // Impossible de placer le tétromino
}

/**
 * Fonction `remove_tetromino`
 * @param b Le plateau de jeu sur lequel retirer le tétromino.
 * @param r La ligne de référence pour le retrait.
 * @param c La colonne de référence pour le retrait.
 * @param t Le tétromino à retirer.
 */

void remove_tetromino(board b, int *r, int *c, tetromino t)
{
    *r = b->nbLignes;
    *c = b->nbColonnes;
    for (int i = 0; i < b->nbLignes; i++)
    {
        for (int j = 0; j < b->nbColonnes; j++)
        {
            if (b->grille[i][j] == get_id(t))
            {
                b->grille[i][j] = 0;
                if (i < *r)
                    *r = i;
                if (j < *c)
                {
                    *c = j;
                }
            }
        }
    }
    if (*r != b->nbLignes)
    {
        for (int j = 0; j < b->nbLignes * b->nbColonnes; j++)
        {
            if (b->bd[j]!=NULL && get_id(b->bd[j]) == get_id(t))
                b->bd[j] = NULL; // Enlever du bd
        }
    }
}

/**
 * Fonction `get_tetromino`
 * @param b Le board sur lequel chercher le tétromino.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @return Le tétromino trouvé ou NULL s'il n'y en a pas.
 */

tetromino get_tetromino(board b, int r, int c)
{
    // Vérifier si la case est vide
    if (b->grille[r][c] == 0)
    {
        return NULL;
    }
    int tetrominoID = b->grille[r][c];
    // Recherche du tétromino correspondant dans le sac
    for (int i = 0; i < b->nbLignes * b->nbColonnes; i++)
    {
        if (get_id(b->bd[i]) == tetrominoID)
        {
            return b->bd[i];
        }
    }
    return NULL; 
}

/**
 * Fonction `get_score`
 * @param b Le plateau de jeu pour lequel récupérer le score.
 * @return Le score actuel du plateau.
 */

int get_score(board b)
{
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return -1; // Valeur de score invalide pour indiquer une erreur
    }
    return b->scoreActuel;
}










/* AJOUT DE CES FONCTIONS SUIVANT LA DEMANDE DE ALI DAOUDI */














/**
 * Fonction `get_nbLignes`
 * @param b Le plateau de jeu.
 * @return Nombre de lignes du plateau.
 */

int get_nbLignes(board b)
{
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return -1; // Valeur de nombre de lignes invalide pour indiquer une erreur
    }
    return b->nbLignes;
}

/**
 * Fonction `nbColonnes`
 * @param b Le plateau de jeu.
 * @return Nombre de colonnes du plateau.
 */

int nbColonnes(board b)
{
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return -1; // Valeur de nombre de colonnes invalide pour indiquer une erreur
    }
    return b->nbColonnes;
}

/**
 * Fonction `tailleSac`
 * @param b Le plateau de jeu.
 * @return Taille du sac de tétromino.
 */

int tailleSac(board b)
{
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return -1; // Valeur de taille du sac invalide pour indiquer une erreur
    }
    return b->tailleSac;
}

/**
 * Fonction `sac`
 * @param b Le plateau de jeu.
 * @return Sac de tétromino.
 */

tetromino *sac(board b)
{
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return NULL;
    }
    return b->sac;
}

/**
 * Fonction `grille`
 * @param b Le plateau de jeu.
 * @return Grille du plateau de jeu.
 */

int **grille(board b)
{
    // Vérifier si le pointeur de plateau est nul
    if (b == NULL)
    {
        printf("Erreur : Le plateau de jeu est NULL !");
        return NULL;
    }
    // Vérifier si le pointeur de grille est nul
    if (b->grille == NULL)
    {
        printf("Erreur : La grille du plateau de jeu est NULL !");
        return NULL;
    }
    return b->grille;
}

/**
 * Tâche E3
 * Fonction 'reserve_tetromino'
 * @param b le plateau.
 * @param t le tetromino concerné.
 * @return 1 si réservé, 0 sinon.
*/

int reserve_tetromino(board b,tetromino t){
    if(b->reserve[0]==NULL){
        int c=0,h=0;
        remove_tetromino(b,&c,&h,t);
        b->reserve[0]=t;
        b->scoreActuel-=get_nb_points(t);
        return 1;
    }
    else{
        printf("réserve pleine!\n");
        return 0;
    }
}

/**
 * Tâche E3
 * Fonction 'remove_tetromino'
 * @param b le plateau.
 * @return rien.
*/

void remove_tetromino_from_reserve(board b){
    if(b->reserve[0]==NULL){
        printf("réserve vide!\n");
        return;
    }
    b->reserve[0]=NULL;
}

/**
 * Tâche E3
 * Fonction 'list_reserve'
 * @param b le plateau.
 * @return le tetromino réservé.
*/

<<<<<<< HEAD
tetromino list_reserve(board b){
    return b->reserve[0];
}
=======
tetromino* list_reserve(board b){
    if(b->reserve[0]==NULL){
        return NULL;
    }
    return b->reserve;
}
>>>>>>> lot_e
