#include "vote_UniAlt.h"

int i_max_tab(int *t,int dim){
    int i_max = 0;
    bool plusieurMax = false;
    int max = t[0];
    int i =1;
    while(i<dim){
        if(t[i] == t[i_max])
            plusieurMax = true;
        if(t[i] > t[i_max]){
            plusieurMax = false;
            i_max = i;}
        i++;
    }
    if(plusieurMax)
        return -1;
    return i_max;
}


t_tab_int_dyn calcul_scores(t_mat_int_dyn votes){
	t_tab_int_dyn scores_candidat;
	creer_t_tab_int_dyn(&scores_candidat,votes.nbRows);
	for(int i=0;i<votes.nbRows;i++){//met à jour le score (nb de votes) pour chaque candidats
		scores_candidat.tab[i] = trouver_votes(i,votes); 
	}
}
int trouver_votes(int candidat,t_mat_int_dyn votes){
	int score = 0;
	for(int i=0;i<votes.nbRows;i++){
		if(i_max_tab(votes.tab[i],votes.nbCol))
			score++;
	}
	return score;
}

int uninominal1(t_mat_int_dyn votes){
	int gagnant = 0;
	t_tab_int_dyn scores_candidat = calcul_scores(votes);//tableau comptabilisant les scores
	gagnant = i_max_tab(scores_candidat.tab,scores_candidat.dim);
	return gagnant;
}

int uninominal2(t_mat_int_dyn votes){
	int gagnant1=-1;
	int gagnant2=-1;
	t_tab_int_dyn scores_candidat = calcul_scores(votes);
	for(int i=0;i<votes.nbCol;i++){//retire les perdants
		if(i != gagnant1 && i != gagnant2)
			del_col_mat(&votes,i);
	}
	return uninominal1(votes); //deuxième tour
}

int i_max_tab(int *t,int dim){
    int i_max = 0;
    bool plusieurMax = false;
    int max = t[0];
    int i =1;
    while(i<dim){
        if(t[i] == t[i_max])
            plusieurMax = true;
        if(t[i] > t[i_max]){
            plusieurMax = false;
            i_max = i;}
        i++;
    }
    if(plusieurMax)
        return -1;
    return i_max;
}