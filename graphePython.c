#include "graphePython.h"

void genererPython(liste l,char *Pygen){
    FILE *origin =NULL;
    FILE *gen =NULL;

    char ligne[MAXCHAR];
    origin = fopen(BASE_FILE,"r");
    gen =fopen(Pygen,"w");
    if(origin == NULL || gen == NULL){
        printf("fichier illisible\n");
        exit(EXIT_FAILURE);
    }

    fgets(ligne,MAXCHAR,origin);
    fprintf(gen,"%s",ligne);
    while(ligne[0] != '#'){
        fgets(ligne,MAXCHAR,origin);
        fprintf(gen,"%s",ligne);
    }

    Elementliste arc;
    while(!emptyList(l)){
        headList(l,&arc);
        delFrontList(&l);
        fprintf(gen,"G.add_edges_from([(%d,%d)],weight=%d)\n"
                                    ,arc.orig,arc.dest,arc.poids);
    }
    while(fgets(ligne,MAXCHAR,origin) != NULL){
        fprintf(gen,"%s",ligne);
    }
    fclose(origin);
    fclose(gen);
}