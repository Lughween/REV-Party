#include <stdio.h>
#include <stdlib.h>
#include "utils_sd.h"

int main(int argc, char const *argv[])
{
	t_tab_int_dyn test;
	creer_t_tab_int_dyn(&test,5);
	init_tab_int(test.tab,5,4);
	affiche_t_tab_int_dyn(test,stdout);
	return 0;
}
