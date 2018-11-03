#include <stdio.h>
#include <stdlib.h>
#include "utils_sd.h"
#include <time.h>

int RandA_B(int a,int b){
    return rand()%(b-a) + a; 
}

int main(int argc, char const *argv[])
{
    FILE *f = NULL;
    f = fopen("log.txt","w");
    int i;
    int j;
    printf("dimension i?\n");
    scanf("%d",&i);
    printf("dimension j?\n");
    scanf("%d",&j);
    t_tab_int_dyn tab;
    t_mat_int_dyn mat;
    //creer_t_tab_int_dyn(&tab,i);
    creer_t_mat_int_dyn(&mat,i,j);
    // init_tab_int(tab.tab,tab.dim,10);
    init_mat_int(mat.tab,mat.nbRows,mat.nbCol,10);
    affiche_t_mat_int_dyn(mat,f);
    fclose(f);
    return 0;
}

