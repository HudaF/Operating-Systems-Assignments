#ifndef MM_H
#define MM_H

typedef struct __node_t
{
    int size;
    struct __node_t *next;
} node_t;

int my_init();
void * my_malloc(int size);
void my_free(void * ptr);
void * my_calloc(int num, int size);
void my_coalesce();
void * my_realloc(void * ptr, int size);
void my_showfreelist();
void my_uninit();
#endif