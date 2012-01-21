# ifndef __GMEM_H__
# define __GMEM_H__

/* Maximal size of heap, for ALL the tasks. Must be huge. Very huge. */
# define __HEAP_SIZE  1048576

/* Uncomment this if you want to use stdlib's malloc() and free() */
/* # define USE_MALLOC */

/*
 * Our implementation of malloc. If a place is found, the memory is
 * filled with zeros.
 * size : asked size to get, positive (a size of 0 will return a NULL
 * 		 pointer).
 * Returns : pointer to an address if there was enough memory,
 * 			 NULL otherwise.
 */
void* gmalloc(unsigned size);

/*
 * Our implementation of free.
 * The pointer ptr must have been allocated by gmalloc, otherwise the
 * program will suddenly exit.
 */
void  gfree(void* ptr);

# endif
