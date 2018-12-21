/* liste statique */
/* Vincent Dugat 2018 */

#ifndef listeSTAT
#define listeSTAT

#include "elementliste.h"
#define DIMMAX 1000 // taille maximale de la liste statique
#define VIDE -1   // constante  pour indiquer que la liste est vide (par convention)
#define ERRLOG "error.log" //fichier de log pour les erreurs
/* ----------------------------------
        Déclaration des types
   --------------------------------*/

struct liste {
    Elementliste Tabliste[DIMMAX];
    int Tete;
    int nbElt;
};

typedef struct liste liste;

void errorMsg(char *msg);//affiche un message d'erreur

int nbEltList(liste lst); // nombre d'éléments
void createList(liste *p); // renvoie une liste statique
void addFrontList(liste *p, Elementliste e); // ajoute un élément devant
void addTailList(liste *p, Elementliste e); // ajoute un élément derrière
void delTailList(liste *p); // supprime l'élément de fin
void delFrontList(liste *p); // supprime l'élément de tête
void headList(liste p, Elementliste *e); // renvoie l'élément de tête
void tailList(liste p, Elementliste *e); // renvoie l'élément de fin
bool emptyList(liste p); // renvoie true si la pile est vide, false sinon
bool fullList(liste p); // renvoie true si la pile est pleine, false sinon
void dumpList(liste p,FILE *fp); // affiche le contenu de la liste
void swapEltList(Elementliste *a,Elementliste *b); // échange deux éléments de la liste
void bubbleSortList(liste *p); // trie la liste
void pickEltList(liste l,Elementliste *e,int index); // renvoie l'élément n° index
bool belongEltList(liste p,Elementliste e); // true si l'élément est dans la liste
bool circuits(liste larc,int nbCandidats);
// renvoi le nb de candidat que rajouterais l'arc
//s'il était rajouter à la liste
int nb_nouveaux_candidat(liste larc,Elementliste arc);
#endif
