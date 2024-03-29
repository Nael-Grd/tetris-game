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
    int tailleSac;   // Taille du sac de tétrominos
    tetromino *sac;  // Sac de tétrominos
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

    // Allouer la mémoire pour le sac de tétrominos
    newBoard->sac = malloc(tailleSac * sizeof(tetromino));
    if (newBoard->sac == NULL)
    {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(MEMORY_ERROR);
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

    // Libérer la mémoire allouée pour le sac de tetrominos
    for (int i =0; i < b->tailleSac; i++)
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
 * @param b Le plateau de jeu contenant le sac de tétrominos.
 * @return Un pointeur vers le sac de tétrominos, ou NULL si le plateau est NULL.
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
 * @param b Le plateau de jeu dans lequel ajouter le tétrominos au sac.
 * @param t Le tétrominos à ajouter au sac.
 */

void add_tetromino_to_bag(board b, tetromino t)
{
    if (b->tailleSac > 0) // # si on a encore de place sinon hahaahah
    {
        // Ajouter le tétromino au sac
        b->sac[b->tailleSac - 1] = t;

        // Décrémenter la taille du sac
        b->tailleSac--;
    }
    else
    {
        // Gérer le cas où le sac est plein
        printf("Erreur : Sac de tétrominos plein. Impossible d'ajouter le tétromino.\n");
    }
}

/**
 * Fonction `remove_tetromino_from_bag`
 * @param b Le plateau de jeu dans lequel retirer le tétrominos du sac.
 * @param t Le tétrominos à retirer du sac.
 */
void remove_tetromino_from_bag(board b, tetromino t)
{
    int index = -1;
    for (int i = 0; i < b->tailleSac; i++)
    {
        if (b->sac[i] == t) // Comparaison basée sur l'adresse mémoire
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        for (int i = index; i < b->tailleSac - 1; i++)
        {
            b->sac[i] = b->sac[i + 1];
        }

        b->tailleSac--;

        if (b->tailleSac > 0)
        {
            tetromino *temp = realloc(b->sac, b->tailleSac * sizeof(tetromino));
            if (temp != NULL)
            {
                b->sac = temp;
            }
            else
            {
                fprintf(stderr, "Erreur : Ré-allocation mémoire impossible.\n");
                exit(MEMORY_ERROR);
            }
        }
        else
        {
            free(b->sac);
            b->sac = NULL;
        }
    }
    else
    {
        printf("Tétromino non trouvé dans le sac.\n");
    }
}

/**
 * Fonction `check_place_tetromino`
 * @param b Le plateau de jeu sur lequel vérifier la possibilité de placer le tétrominos.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétrominos à placer.
 * @return 1 si le tétrominos peut être placé, 0 sinon.
 */
int check_place_tetromino(board b, int r, int c, tetromino t)
{
    // Vérifier si les coordonnées de la grille sont valides
    if (r < 0 || r >= b->nbLignes || c < 0 || c >= b->nbColonnes)
    {
        return PLACEMENT_IMPOSSIBLE; // La cellule est hors de la grille
    }

    // Récupérer les coordonnées des cellules du tétrominos
    int *cells = get_cells(t);
    // Vérifier si le tétrominos peut être placé sans se chevaucher
    for (int i = 0; i < 8; i += 2)
    {
        int cell_r = r + cells[i];     // Coordonnée Y de la cellule du tétrominos
        int cell_c = c + cells[i + 1]; // Coordonnée X de la cellule du tétrominos

        // Vérifier si la cellule est déjà occupée
        if (b->grille[cell_r][cell_c] != 0)
        {
            return PLACEMENT_IMPOSSIBLE;
        }
    }
    return PLACEMENT_POSSIBLE;
}

/**
 * Fonction `place_tetromino`
 * @param b Le plateau de jeu sur lequel placer le tétrominos.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétrominos à placer.
 * @return 1 si le tétrominos a été placé avec succès, 0 sinon.
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
        return 1; // tétrominos placé avec succès    
    }
    return 0; // Impossible de placer le tétrominos
}

/**
 * Fonction `remove_tetromino`
 * @param b Le plateau de jeu sur lequel retirer le tétrominos.
 * @param r La ligne de référence pour le retrait.
 * @param c La colonne de référence pour le retrait.
 * @param t Le tétrominos à retirer.
 */

void remove_tetromino(board b, int *r, int *c, tetromino t)
{
    if (r == NULL || c == NULL)
    {
        fprintf(stderr, "Erreur : pointeurs de référence nuls.\n");
        exit(INVALID_PARAMETERS_ERROR);
    }

    for (int i = 0; i < b->nbLignes; i++)
    {
        for (int j = 0; j < b->nbColonnes; j++)
        {
            if (b->grille[i][j] == get_id(t))
            {
                b->grille[i][j] = 0; // Remettre à 0 pour marquer la case comme vide
            }
        }
    }

    // Réinitialiser les valeurs de référence
    if (r != NULL)
    {
        *r = -1;
    }
    if (c != NULL)
    {
        *c = -1;
    }
}

/**
 * Fonction `get_tetromino`
 * @param b Le board sur lequel chercher le tétrominos.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @return Le tétrominos trouvé ou NULL s'il n'y en a pas.
 */
tetromino get_tetromino(board b, int r, int c)
{
    if (r < 0 || r >= b->nbLignes || c < 0 || c >= b->nbColonnes)
    {
        return NULL; // Coordonnées hors limites
    }

    // Vérifier si la case est vide
    if (b->grille[r][c] == 0)
    {
        return NULL;
    }

    int tetrominoID = b->grille[r][c]; 

    // Recherche du tétrominos correspondant dans le sac
    for (int i = 0; i < b->tailleSac; i++)
    {
        if (get_id(b->sac[i]) == tetrominoID)
        {
            return b->sac[i];
        }
    }
    printf("Tétromino non trouvé dans le sac.\n");
    return NULL;
}

/**
 * Fonction `get_score`
 * @param b Le plateau de jeu pour lequel récupérer le score.
 * @return Le score actuel du plateau.
 */

int get_score(board b)
{
    return b->scoreActuel;
}
