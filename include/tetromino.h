#ifndef __TETROMINO__
#define __TETROMINO__

/*the s_t structure includes:
  an integer table "forme"
  an integer "type"
  an integer "points"
  an integer "id"*/
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




/* E.2 */ 



/* @ requires tetromino has type tetromino
   @ assigns nothing
   @ ensures increments the orientation of tr*/
void turn(tetromino tr, int o);

/**
 * @brief Faire pivoter le tétrimino donné d'un incrément spécifié.
 *
 * Cette fonction modifie l'orientation du tétrimino en ajoutant un incrément à 
 * sa valeur actuelle d'orientation.
 *
 * @param tet Le tétrimino à faire pivoter.
 * @param inc La valeur d'incrémentation de la rotation du tétrimino.
 */
void rotate_tetromino(tetromino tet, int inc);

/**
 * @brief Obtenir l'orientation actuelle du tétrimino.
 *
 * Cette fonction retourne l'orientation actuelle du tétrimino, une valeur entre 0 et 3.
 *
 * @param tet Le tétrimino dont on veut obtenir l'orientation.
 * @return L'orientation actuelle du tétrimino (entre 0 et 3).
 */
int get_rotation(tetromino tet);



#endif
