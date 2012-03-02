#include <setjmp.h>
#include <stdio.h>

static jmp_buf buf;

static int mul(int depth)
{
	int i;
	switch (scanf("%d", &i)) {
		case EOF :
			return 1; /* neutral element */
		case 0 :
			return mul(depth+1); /* erroneous read */
		case 1 :
			if (i)
				return i * mul(depth+1);
			else
				longjmp(buf, 1); /* correct ici, on sort de mul. */
				return 0;
	}
	return 0;
}

int main()
{
	int product;
	setjmp(buf);
	printf("A list of int, please\n");
	product = mul(0);
	printf("product = %d\n", product);
	return 0;
}
