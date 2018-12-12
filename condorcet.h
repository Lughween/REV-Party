// \file condorcet.h
// \author Viala Ludovic
// \date december 2018
#include "lecture_csv.h"
#include "liste.h"

///fonction qui prend une matrice contenant des votes et renvoie sa matrice de duels 
void creer_duel_mat(t_mat_int_dyn *duel_mat, t_mat_int_dyn votes);
void creer_arc_liste(t_mat_int_dyn duels_mat,liste *liste_arc);