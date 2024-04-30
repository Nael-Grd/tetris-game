#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/tetromino.h"

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
    free(b);
}

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
            if (get_id(b->bd[j]) == get_id(t))
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
        b->scoreActuel-=get_score(t);
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
 * @return le tetromino réservé.
*/

tetromino remove_tetromino_from_reserve(board b){
    if(b->reserve[0]==NULL){
        printf("réserve vide!\n");
        return NULL;
    }
    tetromino t=b->reserve[0];
    free(b->reserve[0]);
    return t;
}

/**
 * Tâche E3
 * Fonction 'list_reserve'
 * @param b le plateau.
 * @return la réserve.
*/

tetromino* list_reserve(board b){
    if(b->reserve[0]==NULL){
        return NULL;
    }
    return b->reserve;
}