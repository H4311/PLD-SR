#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;
static int i = 0;

/* Ce programme est erronné car lors du premier longjmp, 
 * l'exécution se fait dans la fonction cpt, alors que l'adresse de
 * retour de la fonction ctp (où doit continuer l'exécution du
 * programme après l'exécution de la fonction) peut ne plus
 * correspondre à rien de cohérent entre temps.
 * */

int cpt()
{
	int j = 0;
	if (setjmp(buf)) {
		for (j=0; j<5; j++)
			i++;
	} else {
		for (j=0; j<4; j++)
			i--;
	}
}
	

int main()
{
	int np = 0 ;
	cpt();
	
	if (! np++) {
		longjmp(buf,~0);
	}
	printf("i = %d\n", i );
}
