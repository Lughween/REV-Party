#include "utils_sd.h"

/****************************création***************************/

int *creer_tab_int(int dim){
    int *tab = calloc(dim,sizeof(int));
    return tab;
}

int **creer_mat_int(int nbRows, int nbCol){
    int **tab = calloc(nbRows,sizeof(int*));
    for(int i =0;i<nbRows;i++){
        tab[i] = calloc(nbCol,sizeof(int));
    }
    return tab;
}

char **creer_tab_str(int dim){
    char **tab = (char**) malloc(dim*sizeof(char*));
    for(int i=0;i<dim;i++){
        tab[i] = calloc(255,sizeof(char));
    }
    return tab;
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

void creer_str_tab_dyn(t_str_tab_dyn *chaines,int dim){
    chaines->dim = dim;
    chaines->tab = creer_tab_str(dim);
}

/*******************************affichage***************************/

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

void affiche_tab_int(int *tab, int dim, FILE *logfp){
    for(int i=0;i<dim;i++){
        fprintf(logfp,"%d ",tab[i]);
    }
    fprintf(logfp,"\n");
}

void affiche_str_tab(t_str_tab_dyn *tab,FILE *logfp){
    for(int i=0;i<tab->dim;i++){
        fprintf(logfp,"%s ",tab->tab[i]);
    }
    fprintf(logfp,"\n");
}

/****************************Initialisation***************************/
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

void init_mat_char(char ***mat,int nbRow,int nbCol,char *val){
    for(int i=0;i<nbRow;i++){
        for(int j=0;j<nbCol;j++){
            mat[i][j] = val;
        }
    }
}

/**************************Comparateur******************************/

bool t_cmp_mat_int(t_mat_int_dyn t1, t_mat_int_dyn t2){
    if(t1.nbCol != t2.nbCol || t1.nbRows != t2.nbRows )
        return false;
    for(int i=0;i<t1.nbRows;i++){
        for(int j=0;j<t1.nbCol;j++){
            if(t1.tab[i][j] != t2.tab[i][j])
                return false;
        }
    }
    return true;
}

bool t_cmp_tab_int(t_tab_int_dyn t1, t_tab_int_dyn t2){
    if(t1.dim != t2.dim)
        return false;
    for(int i=0;i<t1.dim;i++){
        if(t1.tab[i] != t2.tab[i])
            return false;
    }
    return true;
}

/**************************frees******************************/

void free_t_mat_int(t_mat_int_dyn *t){
    for(int i=0;i<t->nbRows;i++){
        free(t->tab[i]);
    }
    free(t->tab);
}

void free_t_tab_int(t_tab_int_dyn *t){
    free(t->tab);
}


void free_str_tab_dyn(t_str_tab_dyn *t){
    free(t->tab);
}

void free_t_mat_char(t_mat_char_star_dyn *t){
    for(int i=0;i<t->nbRows;i++){
        free(t->tab[i]);
    }
    free(t->tab);
}

void add_str_strTab(t_str_tab_dyn *t,int indice,char *str){
    if(indice>=t->dim){
        puts("indice hors tableau\n");
        exit(EXIT_FAILURE);
    }
    //t->tab[indice] = realloc(t->tab[indice],(1+strlen(str))*sizeof(char));
    strcpy(t->tab[indice],str);
}

void del_str_strTab(t_str_tab_dyn *t,int indice){
    int taille = --t->dim;
    char str[CH_MAX];
    for(int i=indice;i<taille;i++){
        strcpy(str,t->tab[i+1]);
        strcpy(t->tab[i],str);
    }
}
void del_col_mat(t_mat_int_dyn *t,int i_col){
    int nb_col = t->nbCol;
    t->nbCol--;
    for(int i=0;i<t->nbRows;i++){
        for(int j=i_col;j<nb_col;j++){
            t->tab[i][j] = t->tab[i][j+1];
        }
    }
}
