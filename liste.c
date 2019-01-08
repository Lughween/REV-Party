#include "liste.h"

//*****************************Utilitaire****************************//

void errorMsg(char *msg){
    FILE *err =NULL;
    err = fopen(ERRLOG,"a+");
    fprintf(err,"erreur:%s",msg);
    fclose(err);
}

//*****************************Information****************************//
int nbEltList(liste l){
    return l.nbElt;
}

bool fullList(liste p){
    if(p.Tete >= DIMMAX-1)
        return true;
    return false;
}

bool emptyList(liste p){
    if(p.Tete == VIDE)
        return true;
    return false;
}


void shiftListUp(liste *p){
    if(fullList(*p)){
        errorMsg("ShiftListUp:pile pleine\n");
        return;
    }
    int i=p->Tete;
    while(i != -1){
        copie_element(&p->Tabliste[i+1],p->Tabliste[i]);
        i--;
    }
    
        
}

void shifListDown(liste *p){
    if(emptyList(*p)){
        errorMsg("shiftListDown:pile vide\n");
        return;
    }
    for(int i=0;i<p->Tete;i++){
        copie_element(&p->Tabliste[i],p->Tabliste[i+1]);
    }
}


//*****************************Gestion****************************//
void createList(liste *p){
    p->Tete = VIDE;
    p->nbElt = 0;
}

void addFrontList(liste *p, Elementliste e){
    if(p->Tete >= DIMMAX){
        errorMsg("addFrontList:pile pleine\n");
        return;
    }
    p->Tete ++;
    p->nbElt++;
    copie_element(&p->Tabliste[p->Tete],e);
}

void addTailList(liste *p, Elementliste e){
    if(p->Tete >= DIMMAX){
        errorMsg("addFrontList:pile pleine\n");
        return;
    }
    shiftListUp(p);
    p->Tete ++;
    p->nbElt++;
    copie_element(&p->Tabliste[0],e);
}

void delTailList(liste *p){
    if(emptyList(*p)){
        errorMsg("delTailList:pile vide\n");
        return;
    }
    shifListDown(p);
    p->Tete--;
    p->nbElt--;
}

void delFrontList(liste *p){
    if(emptyList(*p)){
        errorMsg("delTailList:pile vide\n");
        return;
    }
    p->Tete--;
    p->nbElt--;
}

void headList(liste p,Elementliste *e){
    copie_element(e,p.Tabliste[p.Tete]);
}

void tailList(liste p, Elementliste *e){
    copie_element(e,p.Tabliste[0]);
}

void dumpList(liste p, FILE *fp){
    for(int i=0;i<=p.Tete;i++){
        afficher_element(p.Tabliste[i],fp);
    }
}

void pickEltList(liste l,Elementliste *e,int index){
    if(index > l.Tete){
        errorMsg("picKEltList:indice hors liste\n");
        return;
    }
    copie_element(e,l.Tabliste[index]);
}

bool belongEltList(liste p,Elementliste e){
    if(emptyList(p))
        return false;
    for(int i=0;i<p.Tete;i++){
        if(cmp_elements(e,p.Tabliste[i]))
            return true;
    }
    return false;
}

void swapEltList(Elementliste *a,Elementliste *b){
    Elementliste tmp;
    copie_element(&tmp,*a);
    copie_element(a,*b);
    copie_element(b,tmp);
}

void bubbleSortList(liste *l){
    for(int i=l->Tete;i>=1;i--){
        for(int j=0;j<i;j++){
            if(!est_a_sup_b(l->Tabliste[j+1],l->Tabliste[j]))
                swapEltList(&l->Tabliste[j+1],&l->Tabliste[j]);
        }
    }
}

int nb_nouveaux_candidat(liste larc,Elementliste arc){
    int i=0;
    bool orig = false;
    bool dest = false;
    while(i<=larc.Tete && (!orig || !dest)){
        if(arc.orig == larc.Tabliste[i].orig || arc.orig == larc.Tabliste[i].dest)
            orig = true;
        if(arc.dest == larc.Tabliste[i].orig || arc.dest == larc.Tabliste[i].dest)
            dest =true;
        i++;
    }      
    return !orig + !dest;
}