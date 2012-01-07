#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;
static int i = 0;

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
