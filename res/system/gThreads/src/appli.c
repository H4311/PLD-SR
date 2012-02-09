#include <stdio.h>

#include "gThreads.h"

void letters(void *args)
{
	int i;
	for (i = 0; i<20; ++i) 
	{
		puts("A") ;
		puts("B") ;
		puts("C") ;
	}
}

void numbers(void *args)
{
	int i;
	for (i = 0; i<50; ++i) 
	{
		puts("1") ;
		puts("2") ;
	}
}

int main()
{
	/*
	 * Create two threads
	 */
	
	int lettersId = createGThread("letters", letters, NULL, STACK_SIZE);
	int numbersId = createGThread("numbers", numbers, NULL, STACK_SIZE);
	
	/* Scheduler call */
	startSched();
	
	/*
	killGThread(numbersId);
	killGThread(lettersId);
	*/
	
	return 0;
}
