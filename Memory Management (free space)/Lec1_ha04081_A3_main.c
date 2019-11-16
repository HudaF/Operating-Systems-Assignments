#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mm.h"

int main(int argc, char *argv[])
{
    my_init();

    my_showfreelist();
    printf("\n");

    void * ptr1 = my_malloc(100);
    printf("ptr1 malloc 100\n");
    my_showfreelist();
    printf("\n");

    void * ptr2 = my_malloc(500);
    printf("ptr2 malloc 100\n");
    my_showfreelist();
    printf("\n");

    void * ptr3 = my_malloc(100);
    printf("ptr3 malloc 100\n");
    my_showfreelist();
    printf("\n");
    
    
    printf("ptr1 free 100\n");
    my_free(ptr1);
    my_showfreelist();
    printf("\n");
    
    //printf("\n");
    my_free(ptr2);
    printf("ptr2 free 100\n");
    my_showfreelist();
    printf("\n");

    void* ptr4 = my_malloc(100);
    printf("ptr4 malloc 50\n");
    my_showfreelist();
    printf("\n");

    void* ptr5 = my_malloc(200);
    printf("ptr5 malloc 100\n");
    my_showfreelist();
    printf("\n");

    void* ptr6 = my_calloc(5,50);
    printf("ptr6 calloc 5,50 \n");
    my_showfreelist();
    printf("\n");
	

    void* ptr8 = my_realloc(ptr5,50);
    printf("realloc ptr5 from 200 to 50 \n");
    my_showfreelist();
    printf("\n");

    my_uninit();
    my_showfreelist();
    printf("end \n");
    // char* ptr7 = (char*)ptr6;
    // for(int i=0;i<((5*50));i++)
    // {
    //     if (*ptr7 != 0)
    //     {
    //         printf("%s\n", "calloc not working");
    //     }
    //     ptr7++;
    // }
}
