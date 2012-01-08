#ifndef _GTHREADS_H_
#define _GTHREADS_H_

#define STACK_SIZE 1000
#define NAME_SIZE 16



typedef struct gThread
{  
    int id;
    char name[NAME_SIZE];
    int priority;
    int stackSize;
    
    
    
} gThread;




#endif
