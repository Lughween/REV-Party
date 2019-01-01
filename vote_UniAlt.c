#include "vote_UniAlt.h"

int i_max_tab(int *t,int dim){
    int i_max = 0;
    bool plusieurMax = false;
    int max = t[0];
    int i =1;
    while(i<dim){
        if(t[i] == max)
            plusieurMax = true;
        if(t[i] > max){
            plusieurMax = false;
            i_max = i;
            max = t[i];
            }
        i++;
    }
    if(plusieurMax)
        return -1;
    return i_max;
}

/// \brief calcul le score de chaque candidat et les met dans un tableau à une dimension.
t_tab_int_dyn calcul_scores(t_mat_int_dyn votes){
	t_tab_int_dyn scores_candidat;
    t_tab_int_dyn favorite_cand; //tableau contenant le candidat voté par chaque votant
	creer_t_tab_int_dyn(&scores_candidat,votes.nbCol);
    creer_t_tab_int_dyn(&favorite_cand,votes.nbRows);
    for(int i=0;i<votes.nbRows;i++){
        favorite_cand.tab[i] = i_min_tab(votes.tab[i],votes.nbCol);
    }
    affiche_t_tab_int_dyn(favorite_cand,stdout);
	for(int i=0;i<votes.nbRows;i++){//met à jour le score (nb de votes) pour chaque candidats
		 if(favorite_cand.tab[i]>=0)
            scores_candidat.tab[favorite_cand.tab[i]]++;
	}
    return scores_candidat;
}
/// \brief renvoi le nombre de votes pour un candidat donnée
int trouver_votes(int candidat,t_mat_int_dyn votes){
	int score = 0;
	for(int i=0;i<votes.nbRows;i++){ //pour chaque votant 
        printf("votant:%d i_min!: %d\n",i,i_min_tab(votes.tab[i],votes.nbCol));
		if(i_min_tab(votes.tab[i],votes.nbCol) == candidat) //si candidat est son préférer
            score++;
	}
	return score;
}

char *uninominal1(t_mat_int_dyn votes,t_str_tab_dyn candidats){
	int gagnant = 0;
	t_tab_int_dyn scores_candidat = calcul_scores(votes);//tableau comptabilisant les sco
    printf("score candidat\n");
    affiche_t_tab_int_dyn(scores_candidat,stdout);
	gagnant = i_max_tab(scores_candidat.tab,scores_candidat.dim);
    if(gagnant < 0)
        return "aucun vainqueur";
	return candidats.tab[gagnant];
}

char *uninominal2(t_mat_int_dyn votes,t_str_tab_dyn candidats){
	int gagnant1;
    int gagnant2;
    t_tab_int_dyn scores_candidat = calcul_scores(votes);
    i_2max_tab(scores_candidat.tab,scores_candidat.dim,&gagnant1,&gagnant2);
	for(int i=0;i<votes.nbCol;i++){//retire les perdants
		if(i != gagnant1 && i != gagnant2){
            del_col_mat(&votes,i);
            del_str_strTab(&candidats,i);
        }
	}
	return uninominal1(votes,candidats); //deuxième tour
}

int i_min_tab(int *t,int dim){
    int i_min = 0;
    int min = t[0];
    bool plusieurMin = false;
    int i =1;
    while(i<dim){
        if(t[i] == min)
            plusieurMin = true;
        if(t[i] < min){
            plusieurMin = false;
            min = t[i];
            i_min = i;}
        i++;
    }
    if(plusieurMin)
        return -1;
    return i_min;
}

char *vote_alternatif(t_mat_int_dyn votes,t_str_tab_dyn candidats){
    int perdant = -1;
    while(votes.nbCol != 1){
        t_tab_int_dyn scores_candidat = calcul_scores(votes);
        perdant = i_min_tab(scores_candidat.tab,scores_candidat.dim);
        del_col_mat(&votes,perdant);
        del_str_strTab(&candidats,perdant);
    }
    return candidats.tab[0];
}

void i_2max_tab(int *t,int dim,int *i_max1,int *i_max2){
    *i_max1 = ((t[0]<=t[1])?1:0);
    *i_max2 = ((t[0]>t[1])?1:0);
    // bool tropDeMax = false;
    int max1 = MAX(t[0],t[1]);
    int max2 = MIN(t[0],t[1]);
    int i =2;
    while(i<dim){
        if(t[i] > max1){
            *i_max2 = *i_max1;
            *i_max1 = i;
            max2 = max1;
            max1 = t[i];
        }else if(t[i] > max2){
            *i_max2 = i;
            max2 = t[i];
        }
        i++;
    }
    // if(tropDeMax)
    //     return -1;
}