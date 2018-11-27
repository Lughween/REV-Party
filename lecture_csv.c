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

<<<<<<< HEAD
void lire_csv(char *vote_csv, t_mat_int_dyn *votes){
=======
void lire_csv(char *vote_csv, t_mat_int_dyn *votes,int nb_canditats){
>>>>>>> d88e82c092f32630e1d3bd995f9734430a9c2eba
    FILE *csv = NULL;
    csv = fopen(vote_csv,"r");
    int i_ligne = 0;
    int i_collonne = 0;
    char ligne[TAILLE_MAX];
    char *champ;
    char *svptr;
<<<<<<< HEAD

    int nb_canditats = candidats->dim;
=======
>>>>>>> d88e82c092f32630e1d3bd995f9734430a9c2eba
    if(csv == NULL){
        printf("err::FICHIER:%s ILLISIBLE !\n",vote_csv);
        exit(1);
    }
    while(fgets(ligne,TAILLE_MAX,csv) != NULL){
        del_jump(ligne);
        champ = strtok_r(ligne,DELIM,&svptr);
        // saute le nombres de champ qu'il faut (selon l'offset)
        for(int i=0;i<OFFSET-1;i++){
            champ = strtok_r(NULL,DELIM,&svptr);
        }
        //pour chaque champ du csv le mettre dans la bonne structure
        while(champ != NULL && i_collonne<nb_canditats){
            champ = strtok_r(NULL, DELIM,&svptr);
            if(i_ligne > 0){
                votes->tab[i_ligne-1][i_collonne] = convertir_str_to_int(champ);}
            i_collonne++;
        }
        i_collonne=0;
        i_ligne++;
    }
    fclose(csv);
}
