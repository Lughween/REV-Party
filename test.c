#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "lecture_csv.h"
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define TAILLE_MAX 1000
int RandA_B(int a,int b){
    return rand()%(b-a) + a; 
}

bool cmp_file(char *fich1,char *fich2){
    FILE *f1 = NULL;
    FILE *f2 =NULL;
    f1 = fopen(fich1,"r");
    f2 = fopen(fich2,"r");
    char c1 =getc(f1);
    char c2 =getc(f2);
    while(c1 != EOF && c2 != EOF){
        c1 = getc(f1);
        c2 = getc(f2);
        if(c1 != c2){
            fclose(f1);
            fclose(f2);
            return false;
        }
            
    }
    fclose(f1);
    fclose(f2);
    if(c1 != c2)
        return false;
    return true;
}

void test1(){
    FILE *logz = NULL;
    logz = fopen("tmp.tmp","w");
    t_mat_char_star_dyn mat;
    creer_t_mat_char_dyn(&mat,2,3);
    mat.tab[0][0] = "jean";
    mat.tab[0][1] = "paul";
    mat.tab[0][2] = "michel";
    mat.tab[1][0] = "3";
    mat.tab[1][1] = "4";
    mat.tab[1][2] = "5";
    affiche_t_mat_char_star_dyn(mat,logz);
    fclose(logz);
    assert(cmp_file("fichier_test/test1","tmp.tmp"));
    free_t_mat_char(&mat);
    printf("test0:OK!\n");
}


void test1_csv(){
    FILE *testing = NULL;
    testing = fopen("fichier_test/csv.tmp","w");
    t_mat_int_dyn votes;
    str_tab_dyn candidats;
    creer_str_tab_dyn(&candidats,0);
    creer_t_mat_int_dyn(&votes,0,0);
    printf("test1=ok1\n");
    lire_csv("fichier_test/test1.csv",&candidats,&votes);
    affiche_str_tab(&candidats,testing);
    affiche_t_mat_int_dyn(votes,testing);
    printf("test1=ok2\n");
    free_t_mat_int(&votes);
    free_str_tab_dyn(&candidats);
    fclose(testing);
    assert(cmp_file("fichier_test/testcsv_1","fichier_test/csv.tmp"));
    printf("test1:OK\n");
}


void test2_csv(){ //uniquement les candidats 5 candidats.
    FILE *testing = NULL;
    testing = fopen("fichier_test/csv.tmp","w");
    str_tab_dyn candidats;
    creer_str_tab_dyn(&candidats,5);
    printf("test2=ok1\n");
    csv_get_candidat("fichier_test/test2.csv",&candidats);
    affiche_str_tab(&candidats,testing);
    printf("test2=ok2\n");
    free_str_tab_dyn(&candidats);
    fclose(testing);
    assert(cmp_file("fichier_test/testcsv_2","fichier_test/csv.tmp"));
    printf("test2:OK\n");
}

void test3_csv(){
    FILE *testing = NULL;
    testing = fopen("fichier_test/csv.tmp","w");
    t_mat_int_dyn votes;
    str_tab_dyn candidats;
    creer_str_tab_dyn(&candidats,5);
    creer_t_mat_int_dyn(&votes,10,5);
    printf("test3=ok1\n");
   
    
    csv_get_votes("fichier_test/test3.csv",&votes,5);
    csv_get_candidat("fichier_test/test3.csv",&candidats);
    affiche_str_tab(&candidats,stdout);
    printf("affiche1:OK!\n");
    affiche_t_mat_int_dyn(votes,stdout);
    printf("affiche2:OK!\n");
    csv_get_candidat("fichier_test/test3.csv",&candidats);
    csv_get_votes("fichier_test/test3.csv",&votes,5);
    affiche_str_tab(&candidats,stdout);
    printf("affiche1:OK!\n");
    affiche_t_mat_int_dyn(votes,stdout);
    printf("affiche2:OK!\n");
    free_t_mat_int(&votes);
    free_str_tab_dyn(&candidats);
    fclose(testing);
    assert(cmp_file("fichier_test/testcsv_3","fichier_test/csv.tmp"));
    printf("test3:OK\n");
}
int main(int argc, char const *argv[])
{   
    test1();
    test1_csv();
    test2_csv();
    test3_csv();
    return 0;
}