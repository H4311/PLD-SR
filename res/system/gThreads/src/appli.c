#include <stdio.h>
#include <stdlib.h>

#include "gThreads.h"
#include "gSem.h"

semaphore *sem;

void idle(void *args)
{
	while(1);
}

void letters(void *args)
{
	int i;
	for (i = 0; i<11; i++)
	{
		printf("A");
		printf("B");
		printf("C");
	}
}

void numbers(void *args)
{
	int i;
	/*semTake(sem);*/
	for (i = 0; i<15 ; i++)
	/*while(1)*/
	{
		printf("1");
		printf("2");
	}
}


void others(void *args)
{
	int i;
	for (i = 0; i<13000; ++i) 
	{
		printf("+");
		printf("-");
		printf("*");
		printf("/");
	}
}

void stuff(void *args)
{
	int i;
	for (i = 0; i<11; ++i) 
	{
		printf("X");
		printf("Y");
		printf("Z");
	}
}

void infiniteLol()
{
	int i;
	for (;;i++)
	{
		puts("lol");
	}
	
}

void infiniteTruc()
{
	while(1)
	{
		puts("truc");
	}
}

void infiniteCoucou()
{
	while(1)
	{
		puts("coucou");
	}
}

int main()
{
	/*
	 * Create two threads
	 */
	createGThread("numbers", numbers, NULL, STACK_SIZE);
	createGThread("letters", letters, NULL, STACK_SIZE);
	createGThread("others", others, NULL, STACK_SIZE);
	createGThread("stuff", stuff, NULL, STACK_SIZE);
	
	/*
	createGThread("lol", infiniteLol, NULL, STACK_SIZE);
	createGThread("truc", infiniteTruc, NULL, STACK_SIZE);
	createGThread("coucou", infiniteCoucou, NULL, STACK_SIZE);
	*/
	/*createGThread("others", others, NULL, STACK_SIZE);*/
		
	sem = malloc(sizeof(semaphore));
	semInit(sem,0);
	
	/* Scheduler call */
	startSched();
	
	/*
	killGThread(numbersId);
	killGThread(lettersId);
	*/
	
	printf("Exit application\n");
	return 0;
}
