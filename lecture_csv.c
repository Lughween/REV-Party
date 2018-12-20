#include "lecture_csv.h"

void del_jump(char *ligne){
    char *i = strchr(ligne,'\n');
    if(i != NULL)
        *i = '\0';
}

int convertir_str_to_int(char *str){
    int val=0;
    int k=0;
    while(str[k] !='\0'){
        if(str[k] > 57 || str[k] < 48)
            return -1;
        val = val * 10 + str[k] - '0';
        k++;
    }
    return val;
}


void csv_get_candidat(char *vote_csv,str_tab_dyn *candidats){
    FILE *csv = NULL;
    csv = fopen(vote_csv,"r");
    int i_collonne = 0;
    char ligne[TAILLE_MAX]; //chaine qui récupère la ligne
    char *champ; 
    char *svptr;
    if(csv == NULL){
        printf("err::FICHIER:%s ILLISIBLE !\n",vote_csv);
        exit(1);
    }
    fgets(ligne,TAILLE_MAX,csv);
    del_jump(ligne);
    champ = strtok_r(ligne,DELIM,&svptr);
    for(int i=0;i<OFFSET-1;i++){champ = strtok_r(NULL,DELIM,&svptr);}//saut des champ inutiles

    while(champ != NULL && i_collonne<candidats->dim){
        champ = strtok_r(NULL,DELIM,&svptr);
        candidats->tab[i_collonne] = champ;
        i_collonne++;
    }
    fclose(csv);
}

void csv_get_votes(char *vote_csv,t_mat_int_dyn *votes,int nb_candidats){
    FILE *csv = NULL;
    csv = fopen(vote_csv,"r");
    int i_collonne = 0;
    int i_ligne =0;
    char ligne[TAILLE_MAX]; //chaine qui récupère la ligne
    char *champ; 
    char *svptr;
    if(csv == NULL){
        printf("err::FICHIER:%s ILLISIBLE !\n",vote_csv);
        exit(1);
    }

    while(fgets(ligne,TAILLE_MAX,csv) != NULL){
        del_jump(ligne);
        champ = strtok_r(ligne,DELIM,&svptr);
        for(int i=0;i<OFFSET-1;i++){champ = strtok_r(NULL,DELIM,&svptr);}//saut des champ inutiles
        i_collonne =0;
        while(champ != NULL && i_collonne < nb_candidats){
            champ = strtok_r(NULL,DELIM,&svptr);
                if(i_ligne>0)
                    votes->tab[i_ligne-1][i_collonne] = convertir_str_to_int(champ);
            i_collonne++;
        }
        i_ligne++;
    }
    fclose(csv);
}

void csv_get_duels_mat(char *votes_csv,t_mat_int_dyn *duels_mat,int nb_candidats){
    FILE *csv = NULL;
    csv = fopen(votes_csv,"r");
    int i_collonne = 0;
    int i_ligne =0;
    char ligne[TAILLE_MAX]; //chaine qui récupère la ligne
    char *champ; 
    char *svptr;
    if(csv == NULL){
        printf("err::FICHIER:%s ILLISIBLE !\n",votes_csv);
        exit(1);
    }

    while(fgets(ligne,TAILLE_MAX,csv) != NULL){
        del_jump(ligne);
        champ = strtok_r(ligne,DELIM,&svptr);
        i_collonne =0;
        printf("champ lu :%s\n",champ);
        while(champ != NULL && i_collonne < nb_candidats){
                if(i_ligne>0){
                    printf("champ lu :%s\n",champ);
                    duels_mat->tab[i_ligne-1][i_collonne] = convertir_str_to_int(champ);}
                    champ = strtok_r(NULL,DELIM,&svptr);
            i_collonne++;
        }
        i_ligne++;
    }
    fclose(csv);
}