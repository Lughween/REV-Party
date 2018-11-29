#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define bal_i 0
#define bal_l 1
#define bal_d 2
#define bal_m 3

bool is_bal_i = false;
bool is_bal_d = false;
bool is_bal_l = false;
bool is_bal_m = false;

char **analyse_balise_get_arg(int argc,char const *argv[]){
    char **param_balise; //un tableau de chaine de caractères
    param_balise = malloc(4*sizeof(char*)); // une case par balise possible (max 3 balises)


    int i_arg=1; //numéro argument
    while(i_arg<argc){ //pour chaque argument analyser les balises
        if (argv[i_arg][0] == '-' && i_arg <argc-1){
            if(argv[i_arg][1] == 'i' && !is_bal_i){
                if(is_bal_d){
                    puts("Balise -d et -i sont incompatibles !!\n");
                    exit(EXIT_FAILURE);}
                param_balise[bal_i] = argv[++i_arg];
                is_bal_i = true;
            }
            else if(argv[i_arg][1] == 'd' && !is_bal_d)
            {
                if(is_bal_i){
                    puts("Balise -d et -i sont incompatibles !!\n");
                    exit(EXIT_FAILURE);}
                param_balise[bal_d] = argv[++i_arg];
                is_bal_d = true;
            }
            else if(argv[i_arg][1] == 'l' && !is_bal_l){
                param_balise[bal_l] = argv[++i_arg];
                is_bal_l = true;
            }
            else if(argv[i_arg][1] == 'm' && !is_bal_m){
                param_balise[bal_m] = argv[++i_arg];
                is_bal_m = true;
            }
            else
            {
            puts("erreur argument !\n");
            exit(EXIT_FAILURE);
            }
        }
        else
        {
            puts("erreur argument !\n");
            exit(EXIT_FAILURE);
        }
    }
    return param_balise;  
}

int main(int argc, char const *argv[])
{   
    analyse_balise_get_arg(argc,argv);
    return 0;
}
