#include <stdio.h>

#include "gThreads.h"

void letters(void *args)
{
	int i;
	for (i = 0; i<100; ++i) 
	{
		puts("A") ;
		yield();
		puts("B") ;
		yield();
		puts("C") ;
		yield();
	}
	puts("End letters");
}

void numbers(void *args)
{
	int i;
	for (i = 0; i<100; ++i) 
	{
		puts("1") ;
		yield();
		puts("2") ;
		yield();
	}
	puts("End numbers");
}

int main()
{
	/*
	 * Create two threads
	 */
	
	int lettersId = createGThread("letters", letters, NULL, STACK_SIZE);
	int numbersId = createGThread("numbers", numbers, NULL, STACK_SIZE);
	
	/* Scheduler call */
	yield();
	
	killGThread(numbersId);
	killGThread(lettersId);
	
	return 0;
}
