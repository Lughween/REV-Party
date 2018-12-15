#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include <time.h>
#include <assert.h>
#include <stdbool.h>
#include "graphePython.h"

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


// void test1_csv(){
//     FILE *testing = NULL;
//     testing = fopen("fichier_test/csv.tmp","w");
//     t_mat_int_dyn votes;
//     str_tab_dyn candidats;
//     creer_str_tab_dyn(&candidats,0);
//     creer_t_mat_int_dyn(&votes,0,0);
//     printf("test1=ok1\n");
//     lire_csv("fichier_test/test1.csv",&candidats,&votes);
//     affiche_str_tab(&candidats,testing);
//     affiche_t_mat_int_dyn(votes,testing);
//     printf("test1=ok2\n");
//     free_t_mat_int(&votes);
//     free_str_tab_dyn(&candidats);
//     fclose(testing);
//     assert(cmp_file("fichier_test/testcsv_1","fichier_test/csv.tmp"));
//     printf("test1:OK\n");
// }


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
    affiche_str_tab(&candidats,testing);
    printf("affiche1:OK!\n");
    affiche_t_mat_int_dyn(votes,testing);
    printf("affiche2:OK!\n");
    free_t_mat_int(&votes);
    free_str_tab_dyn(&candidats);
    fclose(testing);
    assert(cmp_file("fichier_test/testcsv_3","fichier_test/csv.tmp"));
    printf("test3:OK\n");
}

void str_test1(){
    printf("0 1 2 2 3\n5 0 3 3 3\n6 4 0 3 3\n7 6 5 0 5\n6 6 5 3 0\n");
}
void test1_duelmat(){
    str_tab_dyn candidats;
    t_mat_int_dyn votes;

    int nb_candidats = 5;
    int nb_votants = 10;
    char csv_test[] = "fichier_test/test3.csv";

    creer_t_mat_int_dyn(&votes,nb_votants,nb_candidats);
    creer_str_tab_dyn(&candidats,nb_candidats);
    
    printf("ok1\n");
    csv_get_votes(csv_test,&votes,nb_candidats);
    

    t_mat_int_dyn duel_mat;
    creer_duel_mat(&duel_mat,votes);
    printf("ok2\n");
    affiche_t_mat_int_dyn(duel_mat,stdout);
    int vainqueur = vainqueur_condorcet(duel_mat);
    csv_get_candidat(csv_test,&candidats);
    if(vainqueur != -1)
        printf("le vainqueur est : %s\n",candidats.tab[vainqueur]);
    else
        printf("il n'y à pas de vainqueur de condorcet :/ ");
    // printf("Résultat attendus :\n");
    // // str_test1();
    // // liste l;
    // // creer_arc_liste(duel_mat,&l);
    // // dumpList(l,stdout);
    // // genererPython(l,"graphe.py");
    free_t_mat_int(&duel_mat);
    free_str_tab_dyn(&candidats);
    free_t_mat_int(&votes);
    
}

void test3_duelmat(){
    str_tab_dyn candidats;
    t_mat_int_dyn votes;

    int nb_candidats = 3;
    int nb_votants = 5;
    char csv_test[] = "fichier_test/test4.csv";

    creer_t_mat_int_dyn(&votes,nb_votants,nb_candidats);
    creer_str_tab_dyn(&candidats,nb_candidats);
    
    printf("ok1\n");
    csv_get_votes(csv_test,&votes,nb_candidats);
    csv_get_candidat(csv_test,&candidats);

    t_mat_int_dyn duel_mat;
    creer_duel_mat(&duel_mat,votes);
    printf("ok2\n");
    affiche_t_mat_int_dyn(duel_mat,stdout);
    // printf("Résultat attendus :\n");
    // str_test1();
    liste l;
    creer_arc_liste(duel_mat,&l);
    dumpList(l,stdout);
    genererPython(l,"graphe.py");
    free_t_mat_int(&duel_mat);
    free_str_tab_dyn(&candidats);
    free_t_mat_int(&votes);
    
}
void test_duelmat_global(){
    str_tab_dyn candidats;
    t_mat_int_dyn votes;

    int nb_candidats = 8;
    int nb_votants = 100;
    system("python votation.py -i michel -v 100 -o fichier_test/test.csv");
    char csv_test[] = "fichier_test/test.csv";

    creer_t_mat_int_dyn(&votes,nb_votants,nb_candidats);
    creer_str_tab_dyn(&candidats,nb_candidats);
    
    printf("ok1\n");
    csv_get_votes(csv_test,&votes,nb_candidats);
    csv_get_candidat(csv_test,&candidats);

    t_mat_int_dyn duel_mat;
    creer_duel_mat(&duel_mat,votes);
    printf("ok2\n");
    affiche_t_mat_int_dyn(duel_mat,stdout);
    // printf("Résultat attendus :\n");
    // str_test1();
    liste l;
    creer_arc_liste(duel_mat,&l);
    dumpList(l,stdout);
    genererPython(l,"graphe.py");
    system("python2.7 graphe.py");
    free_t_mat_int(&duel_mat);
    free_str_tab_dyn(&candidats);
    free_t_mat_int(&votes);
    
}


void test_matrice(){
    t_mat_int_dyn mat;
    t_mat_int_dyn mat2;
    creer_t_mat_int_dyn(&mat2,5,5);
    creer_t_mat_int_dyn(&mat,10,10);
    affiche_t_mat_int_dyn(mat,stdout);
    printf("\n");
    affiche_t_mat_int_dyn(mat2,stdout);
    printf("\n");
    affiche_t_mat_int_dyn(mat,stdout);
}
int main(int argc, char const *argv[])
{   
    // test1();
    // test1_csv();
    // test2_csv();
    // test3_csv();
    test1_duelmat();
    //test2_duelmat();
    //test_duelmat_global();
    //test_matrice();
    return 0;
}