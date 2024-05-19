#include <stdlib.h>
#include "../include/tetromino.h"

/**
 * @brief Structure représentant un tétrimino.
 */
struct tetromino { 
    int unique_id; /**< Un nombre unique qui définit le tétrimino */
    int type; /**< Le type du tétrimino */
    int orientation; /**< L'orientation du tétrimino */
    int points; /**< Le nombre de points du tétrimino */
};

int total_tetrominos = 0;

/**
 * @brief Génère un nouvel identifiant unique.
 *
 * @return Un nouvel identifiant unique.
 */
int generate_unique_id() {
    total_tetrominos += 1;
    return total_tetrominos;
}

/**
 * @brief Crée un tétrimino aléatoire.
 *
 * @return Un nouveau tétrimino.
 */
tetromino create_random_tetromino() {
    tetromino new_tetromino = malloc(sizeof(tetromino));
    new_tetromino->unique_id = generate_unique_id();
    new_tetromino->type = rand() % 7;
    new_tetromino->orientation = 0;
    new_tetromino->points = rand() % 3 + 1;
    return new_tetromino;
}

/**
 * @brief Crée un tétrimino avec des paramètres spécifiques.
 *
 * @param type Le type du tétrimino.
 * @param orientation L'orientation du tétrimino.
 * @param points Le nombre de points du tétrimino.
 * @return Un nouveau tétrimino.
 */
tetromino create_tetromino(int type, int orientation, int points) {
    tetromino new_tetromino = malloc(sizeof(tetromino));
    new_tetromino->unique_id = generate_unique_id();
    new_tetromino->type = type;
    new_tetromino->orientation = orientation;
    new_tetromino->points = points;
    return new_tetromino;
}

/**
 * @brief Libère la mémoire allouée pour un tétrimino.
 *
 * @param tr Le tétrimino à libérer.
 */
void free_tetromino(tetromino tr) {
    free(tr);
}

/**
 * @brief Obtient le type d'un tétrimino.
 *
 * @param tr Le tétrimino.
 * @return Le type du tétrimino, ou -10 si le tétrimino est NULL.
 */
int get_type(tetromino tr) {
    if (tr != NULL)
        return tr->type;
    else
        return -10; // -10 comme valeur absurde, permet d'éviter un segfault, pourra être enlevé lorsque les cas seront mieux gérés
}

/**
 * @brief Obtient l'identifiant unique d'un tétrimino.
 *
 * @param tr Le tétrimino.
 * @return L'identifiant unique du tétrimino, ou -10 si le tétrimino est NULL.
 */
int get_unique_id(tetromino tr) {
    if (tr != NULL)
        return tr->unique_id;
    else 
        return -10;
}

/**
 * @brief Obtient le nombre de points d'un tétrimino.
 *
 * @param tr Le tétrimino.
 * @return Le nombre de points du tétrimino, ou -10 si le tétrimino est NULL.
 */
int get_points(tetromino tr) {
    if (tr != NULL)
        return tr->points;
    else 
        return -10;
}

/**
 * @brief Retourne un tableau contenant les cellules du tétrimino selon les coordonnées.
 *
 * @param tr Le tétrimino.
 * @return Un tableau des cellules du tétrimino.
 */
int* get_tetromino_cells(tetromino tr) {
    int* cells = malloc(sizeof(int) * 8);

    if (tr->type == 0) {
        if (tr->orientation % 2 == 0) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = -1;
            cells[4] = 0; cells[5] = -2;
            cells[6] = 0; cells[7] = -3;
        } else {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = 0;
            cells[4] = -2; cells[5] = 0;
            cells[6] = -3; cells[7] = 0;
        }
    } else if (tr->type == 1) {
        cells[0] = 0; cells[1] = 0;
        cells[2] = 0; cells[3] = -1;
        cells[4] = -1; cells[5] = -1;
        cells[6] = -1; cells[7] = 0;
    } else if (tr->type == 2) {
        cells[0] = 0; cells[1] = 0;
        cells[2] = 0; cells[3] = 1;
        cells[4] = -1; cells[5] = 1;
        cells[6] = -1; cells[7] = 0;
    } else if (tr->type == 3) {
        if (tr->orientation % 4 == 0) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = 0;
            cells[4] = -1; cells[5] = 1;
            cells[6] = -1; cells[7] = 2;
        } else if (tr->orientation % 4 == 1) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = 1;
            cells[4] = -1; cells[5] = 0;
            cells[6] = -2; cells[7] = 0;
        } else if (tr->orientation % 4 == 2) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = 0;
            cells[4] = -1; cells[5] = -1;
            cells[6] = -1; cells[7] = -2;
        } else {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = -1;
            cells[4] = -1; cells[5] = 0;
            cells[6] = -2; cells[7] = 0;
        }
    } else if (tr->type == 4) {
        if (tr->orientation % 2 == 0) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = -2;
            cells[4] = -1; cells[5] = -1;
            cells[6] = -1; cells[7] = 0;
        } else {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = -1;
            cells[4] = -1; cells[5] = -1;
            cells[6] = -2; cells[7] = -1;
        }
    } else if (tr->type == 5) {
        if (tr->orientation % 2 == 0) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = 1;
            cells[4] = -1; cells[5] = 1;
            cells[6] = -1; cells[7] = 2;
        } else {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = -1;
            cells[4] = -1; cells[5] = 0;
            cells[6] = -2; cells[7] = -1;
        }
    } else {
        if (tr->orientation % 2 == 0) {
            cells[0] = 0; cells[1] = 0;
            cells[2] = 0; cells[3] = 1;
            cells[4] = -1; cells[5] = -1;
            cells[6] = -1; cells[7] = 0;
        } else {
            cells[0] = 0; cells[1] = 0;
            cells[2] = -1; cells[3] = 0;
            cells[4] = -1; cells[5] = 1;
            cells[6] = -2; cells[7] = 1;
        }
    }
    return cells;
}
