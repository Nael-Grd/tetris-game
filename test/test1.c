#include "../include/board.h"
#include "../include/tetromino.h"
#include "../include/interface.h"
#include "../include/carte.h"
#include <stddef.h>
#include <CUnit/Basic.h>
#include <stdbool.h>


//Rotation d'une pièce avant placement
void rotation_avant_placement() {
    tetromino t = create_random_tetromino();
    tetromino t1 = t;
    turn(t, 2);                //rotation de 2
    CU_ASSERT_NOT_EQUAL(t, t1); 
    turn(t, 2);
    CU_ASSERT_EQUAL(t, t1); 
    free_tetromino(t);
    free_tetromino(t1);
}

 //Rotation d'une pièce après placement
void rotation_apres_placement() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    tetromino t1 = t;
    place_tetromino(b, 3, 3, t);        //on place le tetromino
    turn(t, 2); 
    CU_ASSERT_NOT_EQUAL(t, t1); 
    turn(t, 2);
    CU_ASSERT_EQUAL(t, t1); 
    free_tetromino(t);
    free_tetromino(t1);
}        

//Rotation d'une pièce après placement (affichage)
void rotation_apres_placement_aff() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    place_tetromino(b, 3, 3, t);       //on place le tetromino
    display_tetromino(t);
    free_tetromino(t);
}

//Placement d'une pièce dans la réserve
void placement_reserve() {               
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    int a = reserve_tetromino(b, t);
    CU_ASSERT(a);
    free_board(b);    //t est compris dans la reserve
}

//Placement d'une pièce dans la réserve (affichage)
void placement_reserve_aff() {               
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    int a = reserve_tetromino(b, t);   //on place t dans la reserve
    display_tetromino(t);
    free_board(b);    
}
   
//Suppression d'une pièce dans la réserve après deux placements
void suppr_2_reserve() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    reserve_tetromino(b, t);                      //on initialise la reserve avec 1 tetro
    tetromino tet1 = create_tetromino(1, 0, 1);   //2 tetromino carrés, orientation 0, 1 point
    tetromino tet2 = create_tetromino(1, 0, 1); 
    place_tetromino(b, 2, 1, tet1);      //on place 2 tetrominos d'affilé
    place_tetromino(b, 2, 3, tet2);
    CU_ASSERT_EQUAL(list_reserve(b), NULL);      //on verifie si la reserve s'est vidée
    free_board(b);
    free_tetromino(t);
    free_tetromino(tet1);
    free_tetromino(tet2);
}
//Récupération d'une carte sur le plateau
void recup_carte() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    carte c = create_carte();    //on créé une carte
    add_card(b, c);        //ajout de la carte sur le plateau
    CU_ASSERT_EQUAL(get_list_of_card(b)[0], c);
    free_card(c);
    free_board(b);
    free_tetromino(t);
}

/* //Récupération d'une carte sur le plateau (affichage)
void recup_cartes_aff() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    carte c = create_carte();   
    add_card(b, c);            //pas de fonction pour afficher une carte
}
*/

//Test des cartes David Roussel, Laurence Bourard, Massinissa Merabet
void test_cartes() {
    board b = create_board(8, 8, 4);
    tetromino t = create_random_tetromino();
    reserve_tetromino(b, t); 
    David_Roussel(b);             //supprime un tetromino de la reserve
    CU_ASSERT_EQUAL(list_reserve(b), NULL);

    tetromino t1 = create_random_tetromino();
    reserve_tetromino(b, t);
    Laurence_Bourard(b, t1);         //echange une piece avec une autre de la reserve
    CU_ASSERT_EQUAL(list_reserve(b), t1);

    remove_tetromino_from_reserve(b);
    Massinissa_Merabet(b);
    CU_ASSERT_NOT_EQUAL(list_reserve(b), NULL);

}


int main() {
    //Initialisation du catalogue
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    //Suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite de tests", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "Test rotation d'une pièce avant placement", rotation_avant_placement)) ||
        (NULL == CU_add_test(pSuite, "Test rotation d'une pièce apres placement", rotation_apres_placement)) ||
        (NULL == CU_add_test(pSuite, "Test d'affichage de rotation d'une pièce apres placement", rotation_apres_placement_aff)) ||
        (NULL == CU_add_test(pSuite, "Test placement d'une pièce dans la réserve", placement_reserve)) ||
        (NULL == CU_add_test(pSuite, "Test superession 2 placements", suppr_2_reserve)) ||
        (NULL == CU_add_test(pSuite, "Test recupération d'une carte sur le plateau", recup_carte)) ||
        (NULL == CU_add_test(pSuite, "Test des cartes David Roussel, Laurence Bourard, Massinissa Merabet", test_cartes)) )
    {
    CU_cleanup_registry();
    return CU_get_error();
    }
   //Affichage des tests
    CU_basic_run_tests();
    CU_basic_show_failures(CU_get_failure_list());

    return 0;
}