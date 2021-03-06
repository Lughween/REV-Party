// \author Ludovic viala
// \file lecture_csv.h
// \date november
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "global.h"
#include "utils_sd.h"

#define TAILLE_MAX 1000
#define DELIM "\t"
#define OFFSET 3


void csv_get_candidat(char *vote_csv,t_str_tab_dyn *candidat); //récupère les candidat du csv
void csv_get_votes(char *vote_csv,t_mat_int_dyn *votes,int nb_candidats); // récupère les votes du csv
//convertit une chaine de caractère contanant un chiffre en int si la chaine
// n'est pas un nombre retourne -1
int convertir_str_to_int(char *str); 
void del_jump(char *ligne); //suprime le retour à la ligne à la fin d'une ligne

void csv_get_duels_mat(char *votes_csv,t_mat_int_dyn *duels_mat,int nb_candidats);
void csv_get_candidat_duels(char *vote_csv,t_str_tab_dyn *candidats);

void csv_compte_ballot(char *csv,int *nb_votants,int *nb_candidats);/// \brief compte le nombre de candidats et de votant dans le csv d'un ballots
void csv_compte_duel(char *csv,int *nb_votants,int *nb_candidats);/// \brief idem pour un csv d'une matrice duels