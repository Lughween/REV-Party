/// \file condorcet.h
/// \author Viala Ludovic
/// \date december 2018
/// \brief permet de trouver un vecteur de condorcet selon les méthodes schulzle, minmax et classement par paires
#include "utils_sd.h"
#include "liste.h"
/// \brief fonction qui prend une matrice contenant des votes et renvoie sa matrice de duels les poid étant le nombre de vote pour le gagnant
void creer_duel_mat(t_mat_int_dyn *duel_mat, t_mat_int_dyn votes);
/// \brief fonction qui prend une matrice contenant des votes et renvoie sa matrice de duels, les poid étant la différence entre les score de chaque candidat pour chaque duel
void creer_arc_liste(t_mat_int_dyn duels_mat,liste *liste_arc);
///\briefcherche un vainqueur de concorcet si il y en à puis retourne son indice sinon -14
int vainqueur_condorcet(t_mat_int_dyn duels_mat);
///\brief cherche un vainqueur de condorcet et applique la méthode min max si besoin
void condorcet_minmax(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants);
///\brief cherche un vainqueur de condorcet et applique la méthode du classement par paire si besoin
void condorcet_paires_class(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants);
/// \brief cherche un vainqueur de condorcet puis applique la méthode de Schuzle si besoin
void condorcet_Schuzle(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants);
///\brief renvoi true si il y a un circuit false sinon
bool circuits(liste larc,int nbCandidats);

