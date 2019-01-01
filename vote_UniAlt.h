
/// \file vote_UniAlt.h
/// \author Viala Ludovic
/// \date dec 2018
/// \brief implémentation du vote alternatif et uninominal 1 et 2;
#include "utils_sd.h"

int i_max_tab(int *t,int dim);
/// \brief renvoi le vainqueur par la méthode vote alternatif
char *vote_alternatif(t_mat_int_dyn votes,t_str_tab_dyn candidats); 
/// \brief renvoi le vainqueur par la méthode uninominal 1 tours
char *uninominal1(t_mat_int_dyn votes,t_str_tab_dyn candidats);
/// \brief renvoi le vainqueur par la méthode uninominal 2 tours
char *uninominal2(t_mat_int_dyn votes,t_str_tab_dyn candidats);
int i_min_tab(int *t,int dim);


