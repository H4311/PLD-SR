# include <stdio.h>

void f2()
{
	// terminale
	// printf("Terminale void sans args.\n");
	int x = 3+7;
	if (x > 3)
		x++;
}

void f1()
{
	printf("Non terminale void sans args\n");
	f2();
}

void f4(int x)
{
	// printf("Terminale void avec args : %d\n", x);
	x++;
}

void f3(int x)
{
	printf("Non terminale void avec args : %d\n", x);
	f4(x);
}

int f6(int x)
{
	//printf("Terminale int avec args : %d\n", x);
	return x+1;
}

int f5(int x)
{
	printf("Non terminale int avec args : %d\n", x);
	return f6(x);
}

int main(int argc, char** argv)
{
	int x = 0;
	f1();
	f3(3);
	x = f5(7);
	return 0;
}
