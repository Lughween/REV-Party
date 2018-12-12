#include "condorcet.h"

void creer_duel_mat(t_mat_int_dyn *duel_mat,t_mat_int_dyn votes){
    int nb_candidat = votes.nbCol;
    int nb_votant = votes.nbRows;
    int nb_win_A_on_B;//variable conptant combien de fois A est préférer à B 
    int nb_win_B_on_A;// idem à l'inverse;
    creer_t_mat_int_dyn(duel_mat,nb_candidat,nb_candidat);
    for(int A = 0;A<nb_candidat;A++){
        for(int B = A;B<nb_candidat;B++){
            nb_win_A_on_B =0;
            nb_win_B_on_A =0;
            if(A!=B)
                for(int votant =0;votant<nb_votant;votant++){
                    if(votes.tab[votant][A] > votes.tab[votant][B]) //si A est préférer à B 
                        nb_win_A_on_B++; 
                    else if(votes.tab[votant][A] < votes.tab[votant][B]) // sinon si inverse sinon rien
                        nb_win_B_on_A++;
                }
            duel_mat->tab[A][B] = nb_win_A_on_B;
            duel_mat->tab[B][A] = nb_win_B_on_A;
        }
    }
}

void creer_arc_liste(t_mat_int_dyn duels_mat,liste *liste_arc){
    Elementliste e;
    for(int i=0;i<duels_mat.nbRows;i++){
        for(int j=0;j<i;j++){
            if(duels_mat.tab[i][j] > duels_mat.tab[j][i]){
                e.orig = i;
                e.dest = j;
                e.poids = duels_mat.tab[i][j];
            }
            else if(duels_mat.tab[i][j] < duels_mat.tab[j][i])
            {
                e.orig = j;
                e.dest = i;
                e.poids = duels_mat.tab[j][i];
            }
            else{
                e.orig = j;
                e.dest = i;
                e.poids = duels_mat.tab[j][i];
                addFrontList(liste_arc,e);
                e.orig = i;
                e.dest = j;
            }
            addFrontList(liste_arc,e);
        }
    }
}