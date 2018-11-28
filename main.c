#include <stdio.h>
#include <stdlib.h>

#define bal_i 0
#define bal_l 1
#define bal_d 2
#define bal_m 3

int main(int argc, char const *argv[])
{
    char **param_balise; //un tableau de chaine de caractères
    param_balise = malloc(4*sizeof(char*)); // une case par balise possible

    int indice_bal_i = -1; //position pour chaque balise de son argument dans param_balise
    int indice_bal_d = -1;
    int indice_bal_l = -1;
    int indice_bal_m = -1;
    int i =-1; //compteur 

    int i_arg=1; //numéro argument
    while(i_arg<argc){
        if (argv[i_arg][0] == '-' && i_arg <argc-1 && i<3){
            if(argv[i_arg][1] == 'i' && indice_bal_d == -1 && indice_bal_i == -1){
                param_balise[++i] = argv[++i];
                indice_bal_i = i;
            }
            else if(argv[i_arg][1] == 'd' && indice_bal_d == -1 && indice_bal_i == -1)
            {
                param_balise[++i] = argv[++i];
                indice_bal_d = i;
            }
            else if(argv[i_arg][1] == 'l' && indice_bal_l == -1){
                param_balise[++i] = argv[++i];
                indice_bal_l = i;
            }
            else if(argv[i_arg][1] == 'm' && indice_bal_m == -1){
                param_balise[++i] = argv[++i];
                indice_bal_m = i;
            }
            else
            {
                puts("erreur argument !\n");
                exit(EXIT_FAILURE);
            }
            
        }
        
        return param_balise;
    }    
    return 0;
}
