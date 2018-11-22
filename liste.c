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
    if(p.Tete = VIDE)
        return true;
    return false;
}


void shiftListUp(liste *p){
    if(fullList(*p)){
        errorMsg("ShiftListUp:pille pleine");
        return;
    }
    int i=p->Tete;
    while(i != -1){
        copie_element(&p->Tabliste[i+1],p->Tabliste[i]);
        i--;
    }
    if(!emptyList(*p))
    {
        p->Tete++;
        p->nbElt++;
    }
        
}

void shifListDown(liste *p){
    if(emptyList(*p)){
        errorMsg("shiftListDown:pile vide");
        return;
    }
    for(int i=0;i<p->Tete;i++){
        copie_element(&p->Tabliste[i],p->Tabliste[i+1]);
    }
    p->Tete--;
    p->nbElt--;
    
}


//*****************************Gestion****************************//
void createList(liste *p){
    p->Tete = VIDE;
    p->nbElt = 0;
}

void addFrontList(liste *p, Elementliste e){
    if(p->Tete >= DIMMAX){
        errorMsg("addFrontList:pile pleine");
        return;
    }
    p->Tete ++;
    p->nbElt++;
    copie_element(&p->Tabliste[p->Tete],e);
}

void addTailList(liste *p, Elementliste e){
    if(p->Tete >= DIMMAX){
        errorMsg("addFrontList:pile pleine");
        return;
    }
    shiftListUp(p);
    copie_element(&p->Tabliste[0],e);
}

void delTailList(liste *p){
    if(emptyList){
        errorMsg("delTailList:pile vide");
        return;
    }
    shifListDown(p);
}

void delFrontList(liste *p){
    if(emptyList){
        errorMsg("delTailList:pile vide");
        return;
    }
    p->Tete--;
    p->nbElt--;
}

void headList(liste p,Elementliste *e){
    copie_element(e,p.Tabliste[p.Tete]);
}

void TailList(liste p, Elementliste *e){
    copie_element(e,p.Tabliste[0]);
}

void dumpList(liste p, FILE *fp){
    for(int i=0;i<p.Tete;i++){
        fprintf(fp,"%d;",p.Tabliste[i]);
    }
}

void pickEltList(liste l,Elementliste *e,int index){
    if(index > l.Tete){
        errorMsg("picKEltList:indice hors liste");
        return;
    }
    copie(e,l.Tabliste[index]);
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



