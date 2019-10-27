// THIS FILE HAVE BEEN TAKEN FROM TUTORIALS POINT AND THEN EDITES AS PER NEED
//LINK: https://www.tutorialspoint.com/pid_structures_algorithms/linked_list_program_in_c.htm

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include   <sys/wait.h>

struct node {
   int pid;
   char* cmd;
   struct node *next;
};

struct node *head = NULL;
struct node *current = NULL;

//display the processes
void printProcesses() {
   struct node *ptr = head;
   printf("PID \t CMD");
   printf("\n");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("%d", ptr->pid);
      printf("\t");
      printf("%s\n",ptr->cmd);
      ptr = ptr->next;
   }
	
}


//insert link at the first location
void insertFirst(char* cmd, int pid) {
   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->cmd = (char *)(malloc(strlen(cmd)* sizeof(char)));
   strcpy(link->cmd, cmd);
   //link->cmd = cmd;
   link->pid = pid;
	
   //point it to old first node
   link->next = head;
	
   //point first to new first node
   head = link;
}

//is list empty
bool isEmpty() {
   return head == NULL;
}

int length() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

int* pidToBeDel()
{
   int* pidToBeDel =  (int *) malloc((length()+1) *sizeof(int));
   struct node *ptr = head;
   int i = 0;
   
   //start from the beginning
   while(ptr != NULL) 
   {
      if(waitpid(ptr->pid, NULL, WNOHANG) != 0)
      {
         pidToBeDel[i] = ptr->pid;
         i++;
      }
      ptr = ptr->next;
   }
   printf("%d\n", i);
   pidToBeDel[i] = -1;
   return pidToBeDel;
   
}



//find a link with given cmd
struct node* find(int pid) {

   //start from the first link
   struct node* current = head;

   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->pid != pid) {
	
      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //go to next link
         current = current->next;
      }
   }      
	
   //if pid found, return the current Link
   return current;
}

//delete a link with given cmd
struct node* delete(int pid) {

   //start from the first link
   struct node* current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //navigate through list
   while(current->pid != pid) {

      //if it is last node
      if(current->next == NULL) {
         return NULL;
      } else {
         //store reference to current link
         previous = current;
         //move to next link
         current = current->next;
      }
   }

   //found a match, update the link
   if(current == head) {
      //change first to point to next link
      head = head->next;
   } else {
      //bypass the current link
      free(current->cmd);
      free(current);
      previous->next = current->next;
   }    
	
   return current;
}
