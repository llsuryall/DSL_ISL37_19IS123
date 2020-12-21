#ifndef MEM_LIB
#define MEM_LIB

#include<stdio.h>

#define mal_error(el,size,r_val,...)\
	if(el==NULL){\
		printf("Unable to allocate %lu bytes of memory - Memory may be insuffecient\n",(long unsigned)size);\
		__VA_OPT__(void * ar[] = { __VA_ARGS__ };\
			for(int i=0;i<sizeof(ar)/sizeof(void *);i++){\
				free(ar[i]);\
			}\
		)\
		return r_val;\
	}\

#endif
