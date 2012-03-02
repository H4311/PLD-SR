#include <setjmp.h>
#include <stdio.h>

int bp, sp;

int testImbrique()
{
	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(bp), "=r"(sp) /* output variables */
	: /* input variables */
	);

	printf("Dans TEST IMBRIQUE :\n");
	printf("Valeur de bp : %d\nValeur de sp : %d\n", bp, sp);
}

int test(int param1, int param2, int param3)
{
	int locale1, locale2, locale3;

	asm ("movl %%ebp, %0" "\n\t" "movl %%esp, %1"
	: "=r"(bp), "=r"(sp) /* output variables */
	: /* input variables */
	);

	printf("Dans TEST :\n");
	printf("Adresse de param1 / param3 : %d / %d\n", &param1, &param3);
	printf("Adresse de locale1 / locale3 : %d / %d\n", &locale1, &locale3);
	printf("Valeur de bp : %d\nValeur de sp : %d\n", bp, sp);
	
	testImbrique();
}

int main()
{
	test(1, 2, 3);

	return 0;
}
