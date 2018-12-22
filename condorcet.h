// \file condorcet.h
// \author Viala Ludovic
// \date december 2018
#include "utils_sd.h"
#include "liste.h"

///fonction qui prend une matrice contenant des votes et renvoie sa matrice de duels 
void creer_duel_mat(t_mat_int_dyn *duel_mat, t_mat_int_dyn votes);
void creer_arc_liste(t_mat_int_dyn duels_mat,liste *liste_arc);
//cherche un vainqueur de concorcet si il y en à puis retourne son indice
//renvoie -1 si il y en à plusieurs
int vainqueur_condorcet(t_mat_int_dyn duels_mat);
//cherche un vainqueur de condorcet et applique la méthode min max si besoin;
int condorcet_minmax(t_mat_int_dyn creer_duels_mat);
int condorcet_paires_class(t_mat_int_dyn duels_mat);
bool circuits(liste larc,int nbCandidats);

