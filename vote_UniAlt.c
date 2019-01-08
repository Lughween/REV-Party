/// \file vote_UniAlt.c
/// \author Viala Ludovic
/// \date december 2018
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
///\brief renvoir les deux maximum d'un tableau
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

int nb_votes_exprimer(t_tab_int_dyn scores){
    int nb_votes =0;
    for(int i=0;i<scores.dim;i++){
        nb_votes += scores.tab[i];
    }
    return nb_votes;
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
	for(int i=0;i<votes.nbRows;i++){//met à jour le score (nb de votes) pour chaque candidats
		 if(favorite_cand.tab[i]>=0)
            scores_candidat.tab[favorite_cand.tab[i]]++;
	}
    free_t_tab_int(&favorite_cand);
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

void uninominal1(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp){
	int gagnant = 0;
	t_tab_int_dyn scores_candidat = calcul_scores(votes);//tableau comptabilisant les sco
    fprintf(logfp,"Uni1 : Score candidat:\n");
    affiche_str_tab(&candidats,logfp);
    affiche_t_tab_int_dyn(scores_candidat,logfp);
	gagnant = i_max_tab(scores_candidat.tab,scores_candidat.dim);
    char str_gagnant[CH_MAX];
    float votes_expr = (float)nb_votes_exprimer(scores_candidat);
    float score = (scores_candidat.tab[gagnant])/votes_expr*100;//% de votes exprimé
    if(gagnant < 0)
        strcpy(str_gagnant,"aucun");
	else
        strcpy(str_gagnant,candidats.tab[gagnant]);
    printf("Mode de Scrutin : Uninominal à 1 Tours, %d candidats, %d votants, vainqueur = %s, score = %.1f\%\n",
        votes.nbCol,votes.nbRows,str_gagnant,score);
    free_t_tab_int(&scores_candidat);
}


void tour2(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp){
    int gagnant = 0;
	t_tab_int_dyn scores_candidat = calcul_scores(votes);//tableau comptabilisant les scores des candidat
    fprintf(logfp,"Uni2 : Score candidat T2:\n");
    affiche_str_tab(&candidats,logfp);
    affiche_t_tab_int_dyn(scores_candidat,logfp);
	gagnant = i_max_tab(scores_candidat.tab,scores_candidat.dim);
    char str_gagnant[CH_MAX];
    if(gagnant < 0)
        strcpy(str_gagnant,"aucun");
	else
        strcpy(str_gagnant,candidats.tab[gagnant]);
    float votes_expr = (float)nb_votes_exprimer(scores_candidat);
    if(votes_expr == 0)
        votes_expr = 1;
    float score = ((scores_candidat.tab[gagnant])/(votes_expr))*100; //% de votes exprimée ou non
    printf("Mode de Scrutin : Uninominal à deux Tours, tour 2, %d candidats, %d votants, vainqueur = %s, score = %1.f\%\n",
        votes.nbCol,votes.nbRows,str_gagnant,score);
}

void init_tour2(t_mat_int_dyn *votes,t_str_tab_dyn *candidats,int gagnant1,int gagnant2){
    t_mat_int_dyn tmp_votes;//structure néscéssaires à l'échange;
    creer_t_mat_int_dyn(&tmp_votes,votes->nbRows,2);
    for(int i=0;i<votes->nbRows;i++){
        tmp_votes.tab[i][0] = votes->tab[i][gagnant1];
        tmp_votes.tab[i][1] = votes->tab[i][gagnant2];
        votes->tab[i][0] = tmp_votes.tab[i][0];
        votes->tab[i][1] = tmp_votes.tab[i][1];
    }
    char *g1 = candidats->tab[gagnant1];
    char *g2 = candidats->tab[gagnant2];
    strcpy(candidats->tab[0],g1);
    strcpy(candidats->tab[1],g2);
    candidats->dim=2;
    votes->nbCol=2;
    free_t_mat_int(&tmp_votes);
}

void uninominal2(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp){
	int gagnant1,gagnant2;
    t_tab_int_dyn scores_candidat = calcul_scores(votes); 

    fprintf(logfp,"Uni2 : Score candidat T1:\n"); 
    affiche_str_tab(&candidats,logfp);
    affiche_t_tab_int_dyn(scores_candidat,logfp);

    i_2max_tab(scores_candidat.tab,scores_candidat.dim,&gagnant1,&gagnant2);

    char str_gagnant[CH_MAX];
    strcpy(str_gagnant,candidats.tab[gagnant1]);
    float votes_expr = (float)nb_votes_exprimer(scores_candidat);
    float score1 = (scores_candidat.tab[gagnant1]/votes_expr)*100; //% de votes exprimée

    printf("Mode de Scrutin : Uninominal à deux Tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.1f\%\n",
        votes.nbCol,votes.nbRows,str_gagnant,score1);
    strcpy(str_gagnant,candidats.tab[gagnant2]);
    float score2 = (scores_candidat.tab[gagnant2]/votes_expr)*100;
    printf("Mode de Scrutin : Uninominal à deux Tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.1f\%\n",
    votes.nbCol,votes.nbRows,str_gagnant,score2);

    init_tour2(&votes,&candidats,gagnant1,gagnant2);
	tour2(votes,candidats,logfp); //deuxième tour
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
/// \brief cherche le minimum d'un tableau autorisant plusieur minimum (renvoi l'indice de la première occurence de celui-ci)
int i_min_tab_plusieur_min(int *t,int dim){
    int i_min = 0;
    int min = t[0];
    int i =1;
    while(i<dim){
        if(t[i] < min){
            min = t[i];
            i_min = i;}
        i++;
    }
    return i_min;
}

void vote_alternatif(t_mat_int_dyn votes,t_str_tab_dyn candidats,FILE *logfp){
    int perdant = -1;
    while(votes.nbCol != 1){
        t_tab_int_dyn scores_candidat = calcul_scores(votes);
        perdant = i_min_tab_plusieur_min(scores_candidat.tab,scores_candidat.dim);
        fprintf(logfp,"Vote Alternatif Score Candidat:\n");
        affiche_str_tab(&candidats,logfp);
        affiche_t_tab_int_dyn(scores_candidat,logfp);
        fprintf(logfp,"Vote Alternatif : Elimination : %s\n",candidats.tab[perdant]);
        del_col_mat(&votes,perdant);
        del_str_strTab(&candidats,perdant);
    }
    printf("Mode de Scrutin : Vote Alternatif, %d candidats, %d votants, vainqueur = %s\n",
    votes.nbCol,votes.nbRows,candidats.tab[0]);
    // free_str_tab_dyn(&candidats);
    // free_t_mat_int(&votes);
}

