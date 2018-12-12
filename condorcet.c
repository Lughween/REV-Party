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