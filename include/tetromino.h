#ifndef __TETROMINO__
#define __TETROMINO__

/*
  the s_t structure includes:
  an integer table "forme"
  an integer "type"
  an integer "points"
  an integer "id"
*/
typedef struct s_t* tetromino;

/*@requires nothing
  @assigns nothing
  @ensures giving a random tetromino*/
tetromino create_random_tetromino();

/*@requires 3 integers: t between 0 and 6, p>0 and o
  @assigns nothing
  @ensures creating a tetromino according to the type (t), orientation (o)
  and number of points (p)*/
tetromino create_tetromino(int t, int o, int p);

/*@requires a tetromino tet
  @assigns tet
  @ensures freeing the space occupied by tet in the memory*/
void free_tetromino(tetromino tet);

/*@requires a tetromino tet
  @assigns nothing
  @ensures giving the type of said tet*/
int get_type(tetromino tet);

/*@requires a tetromino tet
  @assigns nothing
  @ensures giving the unique id of the type of said tet*/
int get_id(tetromino tet);

/*@requires a tetromino tet
  @assigns nothing
  @ensures giving the number of points of said tet*/
int get_nb_points(tetromino tet);

/*@requires a tetromino tet
  @assigns nothing
  @ensures giving a table full of the coordinates of the points of
  said tet*/
int* get_cells(tetromino tet);

/*@requires a tetromino t
  @assigns nothing
  @ensures displaying said tetromino*/
void display_tetromino(tetromino t);




/*
 *@note This part is implemented to address task E.2./**
*/




 * @brief Choose the action to be taken by the player.
 * 
 * @param b The game board.
 * @return The action chosen by the player.
 */
int choose_action(board b);

/**
 * @brief Ask the player where to place the tetromino.
 * 
 * @param b The game board.
 * @param row The chosen row.
 * @param col The chosen column.
 * @param t The tetromino to place.
 * @param state The current state of the game.
 */
void ask_place_tetromino(board b, int *row, int *col, tetromino t, int state);

/**
 * @brief Ask the player if they want to rotate the tetromino.
 * 
 * @param t The tetromino to rotate.
 */
void ask_turn_tetromino(tetromino t);

/**
 * @brief Select a tetromino present on the grid.
 * 
 * @param b The game board.
 * @return The selected tetromino.
 */
tetromino select_tetromino_on_grid(board b);

/**
 * @brief Ask the player if they want to use a special card.
 * 
 * @param b The game board.
 */
void ask_use_card(board *b);



#endif
