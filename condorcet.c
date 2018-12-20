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
                addFrontList(liste_arc,e);
            }
            else if(duels_mat.tab[i][j] < duels_mat.tab[j][i])
            {
                e.orig = j;
                e.dest = i;
                e.poids = duels_mat.tab[j][i];
                addFrontList(liste_arc,e);
            }
            
        }
    }
}

void creer_liste_arc_paire(t_mat_int_dyn duels_mat,liste *liste_arc){
     Elementliste e;
    for(int i=0;i<duels_mat.nbRows;i++){
        for(int j=0;j<i;j++){
            if(duels_mat.tab[i][j] > duels_mat.tab[j][i]){
                e.orig = i;
                e.dest = j;
                e.poids = duels_mat.tab[i][j] - duels_mat.tab[j][i];
                addFrontList(liste_arc,e);
            }
            else if(duels_mat.tab[i][j] < duels_mat.tab[j][i])
            {
                e.orig = j;
                e.dest = i;
                e.poids = duels_mat.tab[j][i] - duels_mat.tab[i][j];
                addFrontList(liste_arc,e);
            }
            
        }
    }
}

int vainqueur_condorcet(t_mat_int_dyn duels_mat){
    bool vainqueur = true;
    int i =0;
    int j;
    while(i<duels_mat.nbRows){
        j=0;
        while(j<duels_mat.nbCol && vainqueur){
            if(duels_mat.tab[i][j] <= duels_mat.tab[j][i] && i != j) //si une défaite le candidta n'est pas vainqueur
                vainqueur = false;
            j++;
        }
        if(vainqueur) //si aucune défaite 
            return i; //retourne l'indice du vainqueur
        i++;
        vainqueur = true;
    }
    return -1; //si aucun gagnant retourne -1
}

int condorcet_minmax(t_mat_int_dyn duels_mat){
    int vainqueur = vainqueur_condorcet(duels_mat);
    affiche_t_mat_int_dyn(duels_mat,stdout);
    if(vainqueur != -1)
        return vainqueur;
    int scoreMinMax; //le meillieurs des pires scores;
    int scoreMinActuel;
    for(int i=0;i<duels_mat.nbRows;i++){
        //printf("scoreMinactuel :%d\n",scoreMinActuel);
        if(i == 0)
            scoreMinActuel = duels_mat.tab[i][1];
        else
            scoreMinActuel = duels_mat.tab[i][0];
        for(int j=0;j<duels_mat.nbCol;j++){
            if(i!=j)
                if(duels_mat.tab[i][j] < scoreMinActuel)
                    scoreMinActuel = duels_mat.tab[i][j];
        }
        if(scoreMinMax < scoreMinActuel){
            scoreMinMax = scoreMinActuel;
            vainqueur = i;
            }
    }
    return vainqueur;
}

int nb_nouveaux_candidat(liste larc,t_arc_p arc){
    int i =0;
    int nb_candidat =2;
    while(i<larc.tete && nb_candidat != 0){
        if(larc.tab)
    }
}

int condorcet_paires_max(t_mat_int_dyn duels_mat){
    liste larcFull;
    creer_liste_arc_paire(duels_mat,&larcFull);
    bubbleSortList(&larcFull);
    liste larcConf;
    Elementliste e;
    headList(larcFull,&e);
    delFrontList(&larcFull);
    addFrontList(&larcConf,e);
    int nb_candidat = 2;

    while(!pileVide(larcFull)){

        if(circuits(larcConf,nb_candidat))
            delFrontList(&larcConf);

        headList(larcFull,&e);
        delFrontList(&larcFull);
        addFrontList(&larcConf,e);
    }
}