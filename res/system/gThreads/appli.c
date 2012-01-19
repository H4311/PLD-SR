#include <stdio.h>

#include "gThreads.h"

typedef void (func_t) (void*);

void letters(void *args)
{
	while(1) 
	{
		printf("A") ;
		yield();
		printf("B") ;
		yield();
		printf("C") ;
		yield();
	}
}
void numbers(void *args)
{
	while(1) 
	{
		printf("1") ;
		yield();
		printf("2") ;
		yield();
	}
}

int main()
{
	int lettersId = createGThread("letters", letters, NULL, STACK_SIZE);
	int numbersId = createGThread("numbers", numbers, NULL, STACK_SIZE);
	
	killGThread(numbersId);
	killGThread(lettersId);
	
	return 0;
}
