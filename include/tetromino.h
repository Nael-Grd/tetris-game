#ifndef __TETROMINO__
#define __TETROMINO__

typedef struct tetromino* tetromino;

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




#endif