/// \file utils_sd.h
/// \author Ludovic Viala
/// \date November 2018
/// \brief tout un ensemble de fonction utilitaire pour la manipulation des structure de données
#ifndef UTILS_SD_H
#define UTILS_SD_H

#include <stdio.h>
#include <stdlib.h>
#include "global.h"

#define OFFSET 3
#define CH_MAX 255

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

/// \struct s_tab_dyn pour encapsuler des tableaux dynamiques d'entiers avec la dimension.
typedef struct s_tab_dyn{
  int * tab;
  int dim;
}t_tab_int_dyn;

typedef struct s_mat_dyn{
  int ** tab;
  int nbRows;
  int nbCol;
} t_mat_int_dyn;

/// \struct s_mat_char_dyn matrice de chaînes de cractères
typedef struct s_mat_char_dyn{
  char *** tab;
  int nbRows;
  int nbCol;
  int offset; // donne le nombre de colonnes avant celles des candidats
} t_mat_char_star_dyn;

typedef struct s_str_tab_dyn{
  char **tab;
  int dim;
}t_str_tab_dyn;

// typedef struct s_tab_str{
//   char **tab;
//   int dim;
// }t_tab_str_dyn;
/// \struct arc pour les graphes
// typedef struct s_arc_p{ /// arc pondéré
//   int orig;
//   int dest;
//   int poids;
// } t_arc_p;

int * creer_tab_int(int dim); // juste un malloc de dim cases
int ** creer_mat_int(int nbRows,int nbCol); // malloc 2D
char **creer_tab_str(int dim);
//char ***creer_mat_char(int nbRows, int nbCol);
void affiche_tab_int(int *tab,int dim, FILE *logfp);

void creer_t_mat_int_dyn(t_mat_int_dyn *stTab,int nbRows,int nbCol); // utilise la struct
void creer_t_tab_int_dyn(t_tab_int_dyn *stTab,int dim); // idem
//void creer_t_mat_char_dyn(t_mat_char_star_dyn * s_tabmots,int nbRows, int nbCol);
void creer_str_tab_dyn(t_str_tab_dyn *chaines,int dim);
void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab, FILE *logfp);
//void affiche_t_mat_char_star_dyn(t_mat_char_star_dyn t_tabmots, FILE *logfp);
void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *logfp);
void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *logfp);
void affiche_str_tab(t_str_tab_dyn *tab,FILE *logfp);

void init_tab_int(int *tab,int dim,int valeur);// initialise avec une valeur
void init_mat_int(int **mat,int nbRows,int nbCol,int valeur); // idem
void init_mat_char(char ***mat,int nbRow,int nbCol,char *val);

//bool t_cmp_mat_int(t_mat_int_dyn t1, t_mat_int_dyn t2);
//bool t_cmp_tab_int(t_tab_int_dyn t1, t_tab_int_dyn t2);

void free_t_mat_int(t_mat_int_dyn *t);
void free_t_tab_int(t_tab_int_dyn *t);
void free_str_tab_dyn(t_str_tab_dyn *t);
//void free_t_mat_char(t_mat_char_star_dyn *t);
void add_str_strTab(t_str_tab_dyn *t,int indice,char *str);
void del_str_strTab(t_str_tab_dyn *t,int indice);
void del_col_mat(t_mat_int_dyn *t,int i_col);

#endif