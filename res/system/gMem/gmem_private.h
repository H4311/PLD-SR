# ifndef __GMEM_PRIVATE_H__
# define __GMEM_PRIVATE_H__

void gmem_printHeader(void* ptr);
int gmem_sizeFreeBlockList();
unsigned gmem_availableMem();
void gmem_show_heap();

void gmem_test0();
void gmem_test1();
void gmem_test2();
void gmem_test3();

# endif
