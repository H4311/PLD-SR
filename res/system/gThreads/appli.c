#include <stdio.h>

#include "gThreads.h"

typedef void (func_t) (void*);

void letters(void *args)
{
	int i;
	for (i = 0; i<100; ++i) 
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
	int i;
	for (i = 0; i<100; ++i) 
	{
		printf("1") ;
		yield();
		printf("2") ;
		yield();
	}
}

int main()
{
	/*
	 * Create two threads
	 */
	
	int lettersId = createGThread("letters", letters, NULL, STACK_SIZE);
	int numbersId = createGThread("numbers", numbers, NULL, STACK_SIZE);
	
	/*yield();*/
	
	killGThread(numbersId);
	killGThread(lettersId);
	
	return 0;
}
