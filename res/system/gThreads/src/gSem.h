#ifndef _GSEM_H_
#define _GSEM_H_

#include "gThreads.h"

/*
 * Sémaphore
 */
struct semaphore {
	int count;
	struct gThread *threads; /* Liste des contextes en attente */
};
typedef struct semaphore semaphore;


#endif
