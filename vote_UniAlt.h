
/// \file vote_UniAlt.h
/// \author Viala Ludovic
/// \date dec 2018
/// \brief implémentation du vote alternatif et uninominal 1 et 2;
#include "utils_sd.h"

int i_max_tab(int *t,int dim);
/// \brief renvoi le vainqueur par la méthode vote alternatif
void vote_alternatif(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp); 
/// \brief renvoi le vainqueur par la méthode uninominal 1 tours
void uninominal1(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp);
/// \brief renvoi le vainqueur par la méthode uninominal 2 tours
void uninominal2(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp);
int i_min_tab(int *t,int dim);


