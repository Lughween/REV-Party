#include "lecture_csv.h"

void del_jump(char *ligne){
    char *i = strchr(ligne,'\n');
    if(i != NULL)
        *i = '\0';
}

void convertir_mat_strToInt(t_mat_int_dyn *votes,t_mat_char_star_dyn mat){
    int val =0;
    int k=0;
    char c;
    for(int i=0;i<mat.nbRows;i++){
        k=0;
        for(int j=0;j<mat.nbCol;j++){
            c = mat.tab[i][j][k];
            while(c != NULL){
                val = val * 10 + c - '0';
                k++;
            }
            votes->tab[i][j] = val;
            val = 0;
        }
    }
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

void lire_csv(char *vote_csv,str_tab_dyn *candidats, t_mat_int_dyn *votes){
    FILE *csv = NULL;
    csv = fopen(vote_csv,"r");
    int i_ligne = 0;
    int i_collonne = 0;
    char ligne[TAILLE_MAX];
    char *champ;

    int nb_canditats = candidats->dim;
    int nb_votant = votes->nbRows;
    if(csv == NULL){
        printf("err::FICHIER:%s ILLISIBLE !\n",vote_csv);
        exit(1);
    }
    while(fgets(ligne,TAILLE_MAX,csv) != NULL){
        del_jump(ligne);
        champ = strtok(ligne,DELIM);
        // saute le nombres de champ qu'il faut (selon l'offset)
        for(int i=0;i<OFFSET-1;i++){
            champ = strtok(NULL,DELIM);
        }
        //pour chaque champ du csv le mettre dans la bonne structure
        while(champ != NULL && i_collonne<nb_canditats){
            champ = strtok(NULL, DELIM);
            if(i_ligne == 0){
                candidats->tab[i_collonne] = champ;}
            if(i_ligne > 0){
                votes->tab[i_ligne-1][i_collonne] = convertir_str_to_int(champ);}
            i_collonne++;
        }
        i_collonne=0;
        i_ligne++;
        for(int i=0;i<nb_canditats;i++){
        printf("%s;",candidats->tab[i]);
    }
    printf("=>%d\n",i_ligne);
    }
    fclose(csv);
}










