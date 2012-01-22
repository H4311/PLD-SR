# ifndef __GMEM_PRIVATE_H__
# define __GMEM_PRIVATE_H__

/* 
 * This file presents functions which allows to debug the heap. All
 * these functions work only with our implementation and not with
 * stdlib.
 * */
 
/*
 * Prints the header associated to a ptr allocated by gmalloc, showing
 * its pointer address, header address, size of memory associated,
 * the memory address (must be equal to pointer address), the next
 * header in the circular list.
 */
void gmem_printHeader(void* ptr);

/*
 * Returns the size of the free block list, ie counts the number of
 * nodes in this list (not the size of memory).
 */
int gmem_sizeFreeBlockList();

/*
 * Returns the available memory in the heap, in bytes.
 */
unsigned gmem_availableMem();

/*
 * Shows the heap in a table, showing the available memory, the address
 * of the heap, and all the nodes with basic infos, which are the header
 * address, the memory address and the end of memory address.
 */
void gmem_show_heap();

/*
 * Test 0 : checks that you can't allocate memory if we asked too much.
 */
void gmem_test0();

/*
 * Test 1 : Allocates and frees memory for one variable.
 */
void gmem_test1();

/*
 * Test 2 : idem as test 2, but on two variables, in order to check
 * if merging works.
 */
void gmem_test2();

/* The great number of allocations and frees, quoted below. */
# define __GMEM_FUNCTIONAL_TEST_TRIES 50000

/*
 * Test 3 : idem as test 3, but on 10 variables, on a great number of
 * allocations and frees, made randomly.
 */
void gmem_test3();

# endif
