#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <math.h>
#include <inttypes.h>
#include "mm.h"

int CHUNK_SIZE = 1024*1024;
node_t * MAGIC_NUMBER = (node_t * )-1; //012345678;



/*setting global variables */
node_t * head = NULL;
node_t * head_save = NULL; // kepning start position for unint
node_t * head_coalesce = NULL; //keeping start position to coalesce linearly

int my_init()
{
   head = mmap(NULL, CHUNK_SIZE, PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE, -1, 0);
   if(head == MAP_FAILED)
   {
       //failure
       return 0;
   }

   head-> size  = CHUNK_SIZE - sizeof(node_t);
   head-> next = NULL;
   head_save = head;
   head_coalesce = head;
   return 1;
}


void my_uninit()
{
    if (head != NULL) //MMAP has been used
    {
        int check_output = munmap(head_save, CHUNK_SIZE);
        if (check_output == 0) //return status
        {
            //putting all in default state for next use of init
            head = NULL;
            head_save = NULL;
            head_coalesce = NULL;
        }
    }
}


void * my_malloc(int size)
{
    node_t* next_temp = head->next;
    int size_temp = head->size;
    void* sptr = NULL; //sptr to return

    if (head->size >= size  + sizeof(node_t))
    {
        head->size = size;
        head->next = MAGIC_NUMBER;

        sptr = head + 1;
        char* temp_head = (char*)head;
        temp_head = temp_head + size + sizeof(node_t);
        head = (node_t *)temp_head;
        head->size = size_temp - size - sizeof(node_t);
        head->next = next_temp;
    }

    //if we malloc after free
    else
    {
        node_t * temp = head;
        while (temp->next != 0 && temp->next->size <= size + sizeof(node_t))
        {
            temp = temp->next;
        }
        //now temp->next is pointing at spcae to be allocated
        node_t* temp2 = temp->next; //to be used for return
        sptr = temp2 + 1;
        int prev_size_allocated = temp2->size;
        node_t* prev_next_allocated = temp2->next;
        temp2->size = size;
        temp2->next = MAGIC_NUMBER;

        int remaining_space = prev_size_allocated - temp2->size;
        if (remaining_space > 0)
        {
            char* split = (char*)temp2;
            split = split + temp2->size + sizeof(node_t);
            node_t * split_node = (node_t *)split;
            split_node->size = remaining_space - sizeof(node_t);
            split_node->next = prev_next_allocated;
            temp->next = split_node;
        }

        else
        {
            temp->next = prev_next_allocated;
        }
    }
    if(sptr==NULL) //failure, no block found which can allocate.
    {
        my_coalesce();
        if (head->size >= size  + sizeof(node_t))
        {
            head->size = size;
            head->next = MAGIC_NUMBER;

            sptr = head + 1;
            char* temp_head = (char*)head;
            temp_head = temp_head + size + sizeof(node_t);
            head = (node_t *)temp_head;
            head->size = size_temp - size - sizeof(node_t);
            head->next = next_temp;
        }

        //if we malloc after free
        else
        {
            node_t * temp = head;
            while (temp->next != 0 && temp->next->size <= size + sizeof(node_t))
            {
                temp = temp->next;
            }
            //now temp->next is pointing at spcae to be allocated
            node_t* temp2 = temp->next; //to be used for return
            sptr = temp2 + 1;
            int prev_size_allocated = temp2->size;
            node_t* prev_next_allocated = temp2->next;
            temp2->size = size;
            temp2->next = MAGIC_NUMBER;

            int remaining_space = prev_size_allocated - temp2->size;
            if (remaining_space > 0)
            {
                char* split = (char*)temp2;
                split = split + temp2->size + sizeof(node_t);
                node_t * split_node = (node_t *)split;
                split_node->size = remaining_space - sizeof(node_t);
                split_node->next = prev_next_allocated;
                temp->next = split_node;
            }

            else
            {
                temp->next = prev_next_allocated;
            }
        }

        }
    else
    {
        return sptr;
    }
}


void my_free (void *ptr)
{
	char* temp = (char*) ptr;
	node_t* temp2 = (node_t *)(temp - sizeof(node_t));
	if (temp2->next == MAGIC_NUMBER) //memory has been allocated
	{
		temp2->next = head; //earlier it was magic
		head=temp2;
	}
}

/*Begin iterating from start of the memory. Makes head where firs unallocated memory block is sound.
If two consecutive blocks are not allocated, they are coalesced, i.e. the sum of both the blocks is made the size of the first one.
Otherwise, move forward to explore new consecutive blocks.*/

void my_coalesce()
{
    head = head_coalesce;
    while (head->next == MAGIC_NUMBER)
    {
        head = (node_t*) ((char*) head + head->size + sizeof(node_t));
    }

    node_t* prev = head;
    node_t* temp1 = head;
    node_t* temp2 = (node_t*)((char*) temp1 + head->size + sizeof(node_t));

    while (temp2 < (node_t*)((char *) head_coalesce + CHUNK_SIZE))
    {
        if (temp1->next != MAGIC_NUMBER && temp2->next != MAGIC_NUMBER) //coalescing condition
        {
            temp1->size = temp1->size + temp2->size + sizeof(node_t);
        }

        else
        {
            temp1 = temp2;
            if (temp1->next!= MAGIC_NUMBER)
	        {
	            prev->next = temp1;
	            prev = temp1;
	        }
        }
        temp2 = (node_t*)((char*) temp2 + temp2->size + sizeof(node_t));
    }
    prev->next = 0;
}

void * my_calloc(int num, int size)
{
    int alloc_size = num*size;
    void * sptr = NULL;
    sptr = my_malloc(alloc_size);
    // void* temp = char*(sptr);
    if (sptr == 0)
    {
        return sptr;
    }
    void* mem = memset(sptr, 0, alloc_size);
    return mem;
}

void * my_realloc(void*ptr, int size)
{
    void* sptr = NULL;
    if(ptr == NULL)
    {
        sptr = my_malloc(size);
        if (sptr == NULL)
        {
            return NULL;
        }
    }

    else
    {
        /* Finding size of the memory allocated by pointer*/
        node_t * temp = (node_t*)ptr;
        temp = temp - 1;
        int ptr_size = temp->size;

        if (ptr_size == size)
        {
            sptr = ptr;
        }

        else
        {
            sptr = my_malloc(size);
            if (sptr == NULL)
            {
                return NULL;
            }
            if(ptr_size < size)
            {
             sptr = memcpy(sptr,ptr,ptr_size); //copy the elements of old block to new block
            }
            else
            {
                sptr = memcpy(sptr,ptr,size);
            }
            my_free(ptr); // free the memory of old block
        }

    }
    return sptr;

}

void my_showfreelist()
{
    int counter = 1;
    node_t* temp = head;
    while (temp!=0)
    {
        printf("%d:%d:%p", counter, temp->size, temp);
        printf("\n");
        counter++;
        temp = temp->next;
    }
}
