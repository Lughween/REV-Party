
/// \file vote_UniAlt.h
/// \author Viala Ludovic
/// \date dec 2018
/// \brief implémentation du vote alternatif et uninominal 1 et 2;
#include "utils_sd.h"

int i_max_t_tab(int *t);
/// \brief renvoi le vainqueur par la méthode vote alternatif
int vote_alternatif(t_mat_int_dyn votes); 
/// \brief renvoi le vainqueur par la méthode uninominal 1 tours
int uninominal1(t_mat_int_dyn votes);
/// \brief renvoi le vainqueur par la méthode uninominal 2 tours
int uninominal2(t_mat_int_dyn votes);





