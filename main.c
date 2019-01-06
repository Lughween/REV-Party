#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "condorcet.h"
#include "vote_UniAlt.h"
#include "lecture_csv.h"

#define bal_i 0
#define bal_l 1
#define bal_d 2
#define bal_m 3

bool is_bal_i = false;
bool is_bal_d = false;
bool is_bal_l = false;
bool is_bal_m = false;

void analyse_balise_get_arg(int argc,char const *argv[], char **param_balise[4]){
    *param_balise = malloc(4*sizeof(char*)); // une case par balise possible (max 3 balises)


    int i_arg=1; //numéro argument
    while(i_arg<argc){ //pour chaque argument analyser les balises
        if (argv[i_arg][0] == '-' && i_arg <argc-1){
            if(argv[i_arg][1] == 'i' && !is_bal_i){
                if(is_bal_d){
                    puts("Balise -d et -i sont incompatibles !!\n");
                    exit(EXIT_FAILURE);}
                param_balise[bal_i] = argv[++i_arg];
                is_bal_i = true;
            }
            else if(argv[i_arg][1] == 'd' && !is_bal_d)
            {
                if(is_bal_i){
                    puts("Balise -d et -i sont incompatibles !!\n");
                    exit(EXIT_FAILURE);}
                param_balise[bal_d] = argv[++i_arg];
                is_bal_d = true;
            }
            else if(argv[i_arg][1] == 'l' && !is_bal_l){
                param_balise[bal_l] = argv[++i_arg];
                is_bal_l = true;
            }
            else if(argv[i_arg][1] == 'm' && !is_bal_m){
                param_balise[bal_m] = argv[++i_arg];
                is_bal_m = true;
            }
            else
            {
            puts("erreur argument !\n");
            exit(EXIT_FAILURE);
            }
            i_arg++;
        }
        else
        {
            puts("pas un argument !\n");
            exit(EXIT_FAILURE);
        }
    } 
}

int main(int argc, char const *argv[])
{   
    char *params[4]; 
    analyse_balise_get_arg(argc,argv,&params);
    FILE *logfp =NULL;
    if(is_bal_l)
        logfp = fopen(params[bal_l],"a+");
    else
        logfp = stdout;
    t_mat_int_dyn votes;
    t_mat_int_dyn duel_mat;
    t_str_tab_dyn candidats;
    int nb_candidat =0;
    int nb_votants =0;
    if(is_bal_i){
        
        csv_compte_ballot(params[bal_i],&nb_votants,&nb_candidat);
        creer_t_mat_int_dyn(&votes,nb_votants,nb_candidat);
        creer_str_tab_dyn(&candidats,nb_candidat);
        csv_get_candidat(params[bal_i],&candidats);
        csv_get_votes(params[bal_i],&votes,candidats.dim);
        creer_duel_mat(&duel_mat,votes);
    }else{
        csv_compte_duel(params[bal_d],&nb_votants,&nb_candidat);
        creer_str_tab_dyn(&candidats,nb_candidat);
        creer_t_mat_int_dyn(&duel_mat,nb_votants,nb_candidat);
        csv_get_candidat_duels(params[bal_d],&candidats);
        csv_get_duels_mat(params[bal_d],&duel_mat,candidats.dim);
    }

    if(is_bal_m){
        if(!strcmp(params[bal_m],"uni1"))
            uninominal1(votes,candidats,logfp);
        else if(!strcmp(params[bal_m],"uni2"))
            uninominal2(votes,candidats,logfp);
        else if(!strcmp(params[bal_m],"cm"))
            condorcet_minmax(duel_mat,candidats,logfp,nb_votants);
        else if(!strcmp(params[bal_m],"cp"))
            condorcet_paires_class(duel_mat,candidats,logfp,nb_votants);
        else if(!strcmp(params[bal_m],"cs"))
            condorcet_Schuzle(duel_mat,candidats,logfp,nb_votants);
        else if(!strcmp(params[bal_m],"va"))
            vote_alternatif(votes,candidats,logfp);
        else
            printf("paramètre de m doit être un des suivant :  uni1,uni2,cm,cp;cs,va !\n");
    }else{
        condorcet_minmax(duel_mat,candidats,logfp,nb_votants);
        printf("\n");
        condorcet_paires_class(duel_mat,candidats,logfp,nb_votants);
        printf("\n");
        condorcet_Schuzle(duel_mat,candidats,logfp,nb_votants);
        printf("\n");
        if(is_bal_i){
        uninominal1(votes,candidats,logfp);
        printf("\n");
        uninominal2(votes,candidats,logfp);
        printf("\n");
        vote_alternatif(votes,candidats,logfp);}
        printf("\n");
        
    }
    if(is_bal_i)
        free_t_mat_int(&votes);
    free_t_mat_int(&duel_mat);
    free_str_tab_dyn(&candidats);
    return 0;
}