#include <setjmp.h>
#include <stdio.h>

static int i = 0;
static jmp_buf buf;

int
main()
{
	int j = 0;
	if (setjmp(buf)) {
		for (; j<5; j++)
			i++;
	} else {
		for (; j<5; j++)
			i--;
		printf("Avant longjump \n");
		longjmp(buf,4);
		printf("Apres longjump \n");
	}
	printf("%d\n", i );
	return 0;
}
