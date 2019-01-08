/// \file condorcet.c
/// \author Viala Ludovic
/// \date december 2018
#include "condorcet.h"


void creer_duel_mat(t_mat_int_dyn *duel_mat,t_mat_int_dyn votes){
    // \brief crée une matrice de duel d'après une matrice contenant les ballots
    int nb_candidat = votes.nbCol;
    int nb_votant = votes.nbRows;
    int nb_win_A_on_B;//variable conptant combien de fois A est préférer à B 
    int nb_win_B_on_A;// idem à l'inverse;
    creer_t_mat_int_dyn(duel_mat,nb_candidat,nb_candidat);
    for(int A = 0;A<nb_candidat;A++){
        for(int B = A;B<nb_candidat;B++){
            nb_win_A_on_B =0;
            nb_win_B_on_A =0;
            if(A!=B)
                for(int votant =0;votant<nb_votant;votant++){
                    if(votes.tab[votant][A] > votes.tab[votant][B]) //si A est préférer à B 
                        nb_win_A_on_B++; 
                    else if(votes.tab[votant][A] < votes.tab[votant][B]) // sinon si inverse sinon rien
                        nb_win_B_on_A++;
                }
            duel_mat->tab[A][B] = nb_win_A_on_B;
            duel_mat->tab[B][A] = nb_win_B_on_A;
        }
    }
}

void creer_arc_liste(t_mat_int_dyn duels_mat,liste *liste_arc){
     Elementliste e;
    for(int i=0;i<duels_mat.nbRows;i++){
        for(int j=0;j<i;j++){
            if(duels_mat.tab[i][j] < duels_mat.tab[j][i]){
                e.orig = i;
                e.dest = j;
                e.poids = duels_mat.tab[j][i] - duels_mat.tab[i][j];
                addFrontList(liste_arc,e);
            }
            else if(duels_mat.tab[i][j] > duels_mat.tab[j][i])
            {
                e.orig = j;
                e.dest = i;
                e.poids = duels_mat.tab[i][j] - duels_mat.tab[j][i];
                addFrontList(liste_arc,e);
            }
        }
    }
}


int vainqueur_condorcet(t_mat_int_dyn duels_mat){
    bool vainqueur = true;
    int i =0;
    int j;
    while(i<duels_mat.nbRows){
        j=0;
        while(j<duels_mat.nbCol && vainqueur){
            if(duels_mat.tab[i][j] <= duels_mat.tab[j][i] && i != j) //si une défaite le candidta n'est pas vainqueur
                vainqueur = false;
            j++;
        }
        if(vainqueur) //si aucune défaite 
            return i; //retourne l'indice du vainqueur
        i++;
        vainqueur = true;
    }
    return -1; //si aucun gagnant retourne -1
}

void condorcet_minmax(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants){
    int vainqueur = vainqueur_condorcet(duels_mat);
    fprintf(logfp,"Minmax : matrice Duels :\n");
    affiche_str_tab(&candidats,logfp);
    affiche_t_mat_int_dyn(duels_mat,logfp);
    if(vainqueur == -1){
        int scoreMinMax =0; //le meillieurs des pires scores;
        int scoreMinActuel = nb_votants;
        for(int i=0;i<duels_mat.nbRows;i++){
            if(i == 0)
                scoreMinActuel = duels_mat.tab[i][1];
            else
                scoreMinActuel = duels_mat.tab[i][0];
            for(int j=0;j<duels_mat.nbCol;j++){
                if(i!=j)
                    if(duels_mat.tab[i][j] < scoreMinActuel)
                        scoreMinActuel = duels_mat.tab[i][j];
            }
            if(scoreMinMax < scoreMinActuel){
                scoreMinMax = scoreMinActuel;
                vainqueur = i;
                }
        }
    }
    char gagnant[CH_MAX];
    if(vainqueur == -1)
        strcpy(gagnant,"aucun gagnant");
    else
        strcpy(gagnant,candidats.tab[vainqueur]);
    printf("Mode de Scrutin : Condorcet Minmax, %d candidats, %d votants, vainqueur = %s\n",
        duels_mat.nbCol,nb_votants,gagnant);
}   

///\brief renvoie vrai si le candidat dans ce graphe-ci à eu une défaite renvoi false sinon
bool a_perdu(int candidats,liste larc){
    Elementliste e;
    while(!emptyList(larc)){
        headList(larc,&e);
        if(e.dest == candidats)
            return true;
        delFrontList(&larc);
    }
    return false;
}

void condorcet_paires_class(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants){
    //int gagnant =vainqueur_condorcet(duels_mat);
    int gagnant =-1;
    if(gagnant == -1){
     liste larc;
     liste arcConfirm;
     createList(&larc);
     createList(&arcConfirm);
     creer_arc_liste(duels_mat,&larc);
     Elementliste e;
     tailList(larc,&e);
     addFrontList(&arcConfirm,e);
     delTailList(&larc);
     int nb_candidat = 2;// il y à forcément 2 candidat quand il n'y à qu'un arc;
     while(!emptyList(larc)){
         tailList(larc,&e);
         nb_candidat += nb_nouveaux_candidat(arcConfirm,e);
         addFrontList(&arcConfirm,e);
         delTailList(&larc);
         if(circuits(arcConfirm,nb_candidat)){
             delFrontList(&arcConfirm);
         }
     }
        for(int i=0;i<nb_candidat;i++){ //trouve le gagnant (celui qui n'a pas perdu)
            if(!a_perdu(i,arcConfirm))
                gagnant = i;
        }
    }
    char vainqueur[CH_MAX];
    if(gagnant == -1)
        strcpy(vainqueur,"aucun gagnant");
    else
        strcpy(vainqueur,candidats.tab[gagnant]);
    printf("Mode de Scrutin : Condorcet classement par paire, %d candidats, %d votants, vainqueur = %s\n",
        duels_mat.nbCol,nb_votants,vainqueur);
}


void eliminer_sommet_graphe(int sommet,liste *larc){
    int taille_debut = nbEltList(*larc);
    Elementliste e = {0,0,0};
    for(int i=0;i<taille_debut;i++){
        headList(*larc,&e);
        delFrontList(larc);
        if(e.orig != sommet && e.dest != sommet)
            addTailList(larc,e);
    }
}


bool est_dans_graphe(int sommet,liste larc){
    bool here = false;
    Elementliste e;
    while(!emptyList(larc) && !here){
        headList(larc,&e);
        delFrontList(&larc);
        if(e.orig == sommet || e.dest == sommet)
            here = true;
    }
    return here;
}
void verifier_candidat_graphe(t_tab_int_dyn *candidats,liste larc,int *nb_candidat_present){
    int nb_cand = candidats->dim;
    for(int i=0;i<nb_cand;i++){
        if(!est_dans_graphe(i,larc) && candidats->tab[i] == 1  ){
            candidats->tab[i] =0;
            *nb_candidat_present = *nb_candidat_present-1;
            }
    }       
}
///\brief verifie si le candidat fait partie de son ensemble de Schwarz (https://fr.wikipedia.org/wiki/M%C3%A9thode_Schulze 
/// (cf. Heuristique de l'ensemble de Schwartz)) et l'élimine si ce n'est pas le cas
void Eliminer_Somment_Non_Scharwz(t_tab_int_dyn *candidats,liste *larc,int *nb_candidat_present){
    for(int i=0;i<=larc->Tete;i++){
        if(a_perdu(i,*larc)){
            eliminer_sommet_graphe(i,larc);
            candidats->tab[i] = 0;
            *nb_candidat_present = *nb_candidat_present-1;
        }
    }
    verifier_candidat_graphe(candidats,*larc,nb_candidat_present);
}


void condorcet_Schuzle(t_mat_int_dyn duels_mat,t_str_tab_dyn candidats,FILE *logfp,int nb_votants){
    int gagnant = vainqueur_condorcet(duels_mat);

    if(gagnant == -1){
        int nb_candidat_present = candidats.dim;
        liste larc;
        t_tab_int_dyn liste_candidat_present;
        creer_t_tab_int_dyn(&liste_candidat_present,candidats.dim);
        init_tab_int(liste_candidat_present.tab,candidats.dim,1);
        createList(&larc);
        creer_arc_liste(duels_mat,&larc);
        bubbleSortList(&larc);
        fprintf(logfp,"Schuzle : liste arc :\n");
        dumpList(larc,logfp);
        fprintf(logfp,"Schuzle : candidat présent :\n");
        affiche_str_tab(&candidats,logfp);
        affiche_t_tab_int_dyn(liste_candidat_present,logfp);
        Eliminer_Somment_Non_Scharwz(&liste_candidat_present,&larc,&nb_candidat_present);
        
        while(!emptyList(larc) && nb_candidat_present >1){
            fprintf(logfp,"Schuzle : liste arc :\n");
            dumpList(larc,logfp);
            fprintf(logfp,"Schuzle : candidat présent :\n");
            affiche_str_tab(&candidats,logfp);
            affiche_t_tab_int_dyn(liste_candidat_present,logfp);
            Eliminer_Somment_Non_Scharwz(&liste_candidat_present,&larc,&nb_candidat_present);
            delFrontList(&larc);
        }
        affiche_t_tab_int_dyn(liste_candidat_present,logfp);
        bool isGagnant = false;
        for(int i=0;i<candidats.dim;i++){
            if(liste_candidat_present.tab[i] == 1){
                if(isGagnant)
                    gagnant = -1;
                else{
                    gagnant = i;
                    isGagnant =true;
                    }
            }
        }
        free_t_tab_int(&liste_candidat_present);
        // free_t_mat_int(&duels_mat);
        // free_t_tab_int(&candidats);
    }
    char vainqueur[CH_MAX];
    if(gagnant == -1)
        strcpy(vainqueur,"aucun gagnant");
    else
        strcpy(vainqueur,candidats.tab[gagnant]);
    printf("Mode de Scrutin : Condorcet Schuzle, %d candidats, %d votants, vainqueur = %s\n",
        duels_mat.nbCol,nb_votants,vainqueur);
        
}