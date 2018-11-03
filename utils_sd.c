#include "utils_sd.h"

int *creer_tab_int(int dim){
    int *tab = malloc(dim*sizeof(int));
    return tab;
}

int **creer_mat_int(int nbRows, int nbCol){
    int **tab = malloc(nbRows*sizeof(int*));
    for(int i =0;i<nbRows;i++){
        tab[i] = malloc(nbCol*sizeof(int));
    }
    return tab;
}

void affiche_tab_int(int *tab, int dim, FILE *logfp){
    for(int i=0;i<dim;i++){
        fprintf(logfp,"%d;",tab[i]);
    }
    fprintf(logfp,"\n");
}

void creer_t_mat_int_dyn(t_mat_int_dyn * stTab, int nbRows, int nbCol){
    stTab->tab = creer_mat_int(nbRows,nbCol);
    stTab->nbCol = nbCol;
    stTab->nbRows = nbRows;
}

void creer_t_tab_int_dyn(t_tab_int_dyn * stTab, int dim){
    stTab->tab = creer_tab_int(dim);
    stTab->dim = dim;
}

void affiche_t_tab_int_dyn(t_tab_int_dyn t_tab,FILE *logfp){
    affiche_tab_int(t_tab.tab,t_tab.dim,logfp);
}

void affiche_mat_int(int **duels_mat,int nbRows,int nbCol,FILE *logfp){
    for(int i=0;i<nbRows;i++){
        affiche_tab_int(duels_mat[i],nbCol,logfp);
    }
}

void affiche_t_mat_int_dyn(t_mat_int_dyn t_tab, FILE *logfp){
    affiche_mat_int(t_tab.tab,t_tab.nbRows,t_tab.nbCol,logfp);
}

void init_tab_int(int *tab,int dim,int valeur){
    for(int i=0;i<dim;i++){
        tab[i] = valeur;
    }
}

void init_mat_int(int **mat, int nbRows,int nbCol,int val){
    for(int i=0;i<nbRows;i++){
        init_tab_int(mat[i],nbCol,val);
    }
}