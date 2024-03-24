#include <stdio.h>
#include <stdlib.h>
#include "../include/board.h"
#include "../include/tetromino.h"

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
 * @param tailleSac La taille initiale du sac de tétraminos.
 * @return Le plateau de jeu nouvellement créé.
 */

board create_board(int nbLignes, int nbColonnes, int tailleSac)
{
    // Allouer la mémoire nécessaire pour la structure BoardStruct
    board newBoard = (board)malloc(sizeof(struct BoardStruct));

    // Initialiser les membres de la structure selon les paramètres
    newBoard->nbLignes = nbLignes;
    newBoard->nbColonnes = nbColonnes;
    newBoard->tailleSac = tailleSac;
    newBoard->scoreActuel = 0;

    // Allouer la mémoire pour le sac de tétrominos
    newBoard->sac = (tetromino *)malloc(tailleSac * sizeof(Tetromino));

    // Allouer la mémoire pour la grille du plateau de jeu
    newBoard->grille = (int **)malloc(nbLignes * sizeof(int *));
    for (int i = 0; i < nbLignes; i++)
    {
        newBoard->grille[i] = (int *)malloc(nbColonnes * sizeof(int));
        // Initialiser la grille à des valeurs par défaut
        for (int j = 0; j < nbColonnes; j++)
        {
            newBoard->grille[i][j] = 0; // 0 signifie une case vide,
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
    // Libérer la mémoire allouée pour le sac de tétrominos
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
 * @param b Le plateau de jeu contenant le sac de tétraminos.
 * @return Un pointeur vers le sac de tétraminos.
 */

tetromino *list_tetrominos_in_bag(board b)
{
    return b->sac;
}

/**
 * Fonction `add_tetromino_to_bag`
 * @param b Le plateau de jeu dans lequel ajouter le tétraminos au sac.
 * @param t Le tétraminos à ajouter au sac.
 */

void add_tetromino_to_bag(board b, Tetromino t)
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
        // Gérer le cas où le sac est plein (vous voudrez peut-être gérer cette situation en conséquence)
        printf("Erreur : Sac de tétrominos plein. Impossible d'ajouter le tétromino.\n");
    }
}

/**
 * Fonction `remove_tetromino_from_bag`
 * @param b Le plateau de jeu dans lequel retirer le tétraminos du sac.
 * @param t Le tétraminos à retirer du sac.
 */

void remove_tetromino_from_bag(board b, Tetromino t)
{
    int index = -1;
    for (int i = 0; i < b->tailleSac; i++)
    {
        if (b->sac[i] == t)
        {
            index = i;
            break;
        }
    }

    // Si le tétromino est trouvé dans le sac, le retirer
    if (index != -1)
    {
        for (int i = index; i < b->tailleSac - 1; i++)
        {
            b->sac[i] = b->sac[i + 1];
        }

        b->tailleSac--;

        b->sac = (Tetromino *)realloc(b->sac, b->tailleSac * sizeof(Tetromino));
    }
    else
    {
        printf("Tétromino non trouvé dans le sac.\n");
    }
}

/**
 * Fonction `check_place_tetromino`
 * @param b Le plateau de jeu sur lequel vérifier la possibilité de placer le tétraminos.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétraminos à placer.
 * @return 1 si le tétraminos peut être placé, 0 sinon.
 */

int check_place_tetromino(board b, int r, int c, tetromino t)
{
    // Récupérer les coordonnées des cellules du tétromino
    int *cells = get_cells(t);
    int nb_points = get_nb_points(t); // Vérifier si la cellule est hors de la grille
    if (r < 0 || r >= b->nbLignes || c < 0 || c >= b->nbColonnes)
    {
        return 0; // La cellule est hors de la grille
    }             // Vérifier si le tétromino peut être placé sans se chevaucher
    for (int i = 0; i < 2 * nb_points; i += 2)
    {
        int cell_r = r + cells[i];     // Coordonnée Y de la cellule du tétromino
        int cell_c = c + cells[i + 1]; // Coordonnée X de la cellule du tétromino
        if (b->grille[cell_r][cell_c] != 0)
        {
            return 0; // La cellule est déjà occupée
        }
    }
    return 1;
}

/**
 * Fonction `place_tetromino`
 * @param b Le plateau de jeu sur lequel placer le tétraminos.
 * @param r La ligne de référence pour le placement.
 * @param c La colonne de référence pour le placement.
 * @param t Le tétraminos à placer.
 * @return 1 si le tétraminos a été placé avec succès, 0 sinon.
 */

int place_tetromino(board b, int r, int c, Tetromino t)
{
    if (check_place_tetromino(b, r, c, t))
    {
        int *cells = get_cells(t);
        int nb_points = get_nb_points(t);
        for (int i = 0; i < 2 * nb_points; i += 2)
        {
            b->grille[r + cells[i]][c + cells[i + 1]] = get_id(t); // Utiliser l'ID du tétraminos pour marquer sa présence
        }
        return 1; // Tétraminos placé avec succès
    }
    return 0; // Impossible de placer le tétraminos
}

/**
 * Fonction `remove_tetromino`
 * @param b Le plateau de jeu sur lequel retirer le tétraminos.
 * @param r La ligne de référence pour le retrait.
 * @param c La colonne de référence pour le retrait.
 * @param t Le tétraminos à retirer.
 */

void remove_tetromino(board b, int *r, int *c, Tetromino t)
{
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
    *r = -1;
    *c = -1;
}

/**
 * Fonction `get_tetromino`
 * @param b Le board sur lequel chercher le tétraminos.
 * @param r La ligne de référence.
 * @param c La colonne de référence.
 * @return Le tétraminos trouvé ou NULL s'il n'y en a pas.
 */

tetromino get_tetromino(board b, int r, int c)
{
    if (r < 0 || r >= b->n || c < 0 || c >= b->m)
    {
        return NULL; // Coordonnées hors limites
    }

    // Vérifier si la case est vide
    if (b->grid[r][c] == 0)
    {
        return NULL;
    }

    // Récupérer le tétraminos à la case indiquée
    int indexTetromino = b->grid[r][c] - 1; // On décrémente car les indices commencent à 0
    return b->bag->tetriminos[indexTetromino];
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
