/** \file graphePython.h
 * 	\author Viala ludovic
 * 	\date dec 2018
 * 	\brief génère un fichier python permettant d'afficher un graphes orienté d'une liste
 * 		d'arcs.
 */

#include "liste.h"

#define BASE_FILE "poltest.py"
#define MAXCHAR 255

void genererPython(liste l,char *Pygen);