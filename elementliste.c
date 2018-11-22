#include "elementliste.h"

void saisie_element(Elementliste *elt){
    printf("origine?\n");
    scanf("%d",&elt->orig);
    printf("destination?\n");
    scanf("%d",&elt->dest);
    printf("poids?\n");
    scanf("%d",&elt->poids);
}


void copie_element(Elementliste *dest, Elementliste source){
    dest->poids = source.poids;
    dest->orig = source.orig;
    dest->dest = source.dest;
}

void afficher_element(Elementliste e,FILE *fp){
    fprintf(fp,"%d;%d;%d\n",e.orig,e.dest,e.poids);
}

bool cmp_element(Elementliste e1, Elementliste e2){
    if(e1.poids == e2.poids && e1.orig == e2.orig 
        && e1.dest == e2.dest)
        return true;
    return false;
}