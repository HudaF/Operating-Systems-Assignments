#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <fcntl.h>
#include <assert.h>
#define ANSI_COLOR_RED "\x1b[31m"

// THIS LinkedLIST HAVE BEEN TAKEN FROM TUTORIALS POINT AND THEN EDITEd AS PER NEED
//LINK: https://www.tutorialspoint.com/pid_structures_algorithms/linked_list_program_in_c.htm

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
   //printf("%d\n", i);
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

void delAllNodes()
{
	struct node *ptr = head;
	while(!isEmpty())   //killing all processes and freeing the space
	{
		kill(ptr->pid, SIGTERM);
		free(current->cmd);
      	free(current);
      	ptr = ptr->next;
	}
}
void pwd(char* strpwd, int display)
{
	char temp[1000];
	char* cd = getcwd(temp,sizeof(temp));
	if (cd == NULL)
	{
		perror("  Error in getting pwd:");
	}
	else
	{
		strcpy(strpwd,temp);
		if (display == 1)
		{
			printf("%s\n",strpwd );
		}
	}
}


char** parsed(char* str_input, char * delim, int* howManyParsed)
{
	char* forParsedLength;
	*howManyParsed = 0;
	char str_input_copy[strlen(str_input)];
	strcpy(str_input_copy, str_input);
	char* parsedWord;
	forParsedLength = strtok(str_input_copy, delim);

	while( forParsedLength != NULL ) //calculating the length of the str_input
	{
      (*howManyParsed)++;
      forParsedLength = strtok(NULL, delim);
   }
   
   parsedWord = strtok(str_input, delim);
   char** parsedList = (char **)malloc((*howManyParsed) * sizeof(char*));   //using that calcuated length to make dynamic array of char
   for(int i=0; i< *howManyParsed; i++)
   {
   	parsedList[i] = parsedWord;
   	parsedWord = strtok(NULL, delim);
   	
   }
   return parsedList;
}

void cd (char * workingDirectory)
{
	if (chdir(workingDirectory) != 0)
	{
		perror(" No such file or directory");
	}
	else
	{
		chdir(workingDirectory);	//changing current directory
	}
}

void delDeadChild()
{
	int* pidToGetDel = pidToBeDel();
	int i =0;
	while(pidToGetDel[i]!= -1)
	{
	
		delete(pidToGetDel[i]);  //deleting the node of dead processes
		i++;
	}
}

void myps()
{
	delDeadChild();
	printProcesses();  //after deleting dead processes printing alive one
}

void modifyPath(char* currentDir)
{
	char * str1 = (char *)malloc(2048 * sizeof(char));
	str1 = getenv("PATH");
	char* str2 = ":.";   //appending dot in the path will allow us to work in whatever directory we are
	strcat(str1,str2);
	//strcat(str1,currentDir);
	setenv("PATH",str1,1);
	//printf("%s\n", getenv("PATH"));
}


void VarPath(char* var, char* val)
{
	setenv(var, val, 1);
}


void mylsenv(char** envpAll)
{

	char **envp_copy = envpAll;
	for (envp_copy; *envp_copy != 0; envp_copy++)
	{
		 printf("%s\n", *envp_copy);    //displaying all the environment variables
	}
}


void showVar(char* var)
{
	if (getenv(var) == NULL)
	{
		printf("%s\n","Variable Does not exist" );
	}
	else
	{
		printf("%s\n", getenv(var));
	}
	
}

void interlude(int* parsedsize, char* str_input, char* cwd, char ** envp)
{
	char **argv;
	char ** amp_parsed;
	char ** redir_parsed;
	int argc = 0;
	int amp_count = 0;
	int redir_cont = 0;

	amp_parsed = parsed(str_input, "&\n",parsedsize);
	amp_count= *parsedsize;

	for (int i = 0; i < amp_count; i++)
	{
		redir_parsed =  parsed(amp_parsed[i], ">\n",parsedsize);
		redir_cont = *parsedsize;

		//printf("\n process complete \n");
		argv = parsed(redir_parsed[0], " \n",parsedsize);
		argc = *parsedsize;

		if (strlen(argv[0]) == 0)
		{
			continue;
		}
		if (strcmp(argv[0],"pwd")==0)
		{
			pwd(cwd,1);
			break;
		}

		else if (strcmp(argv[0],"cd")==0)
		{
			cd(argv[1]);
			break;
		}

		else if (strcmp(argv[0],"mylsenv")==0)
		{
			//mylsenv(envp);
			//break;
			argv[0] = "env";
		}

		else if (strcmp(argv[0],"myps")==0)
		{
			myps();
			break;
		}

	    //printf("hello world (pid:%d)\n", (int) getpid());
	    int rc = fork();

	    if (rc < 0) 
	    {
	        // fork failed; exit
	        fprintf(stderr, "fork failed\n");
	        exit(1);
	    } 

	    else if (rc == 0) 
	    {
	    	//printf("\n idhar in fork \n" );
	        // child (new process)
	        //printf("hello, I am child (pid:%d)\n", (int) getpid());
	        if (redir_cont>1)
	        {
	        	close(STDOUT_FILENO);
	        	open(redir_parsed[redir_cont-1], O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
	        }

	        char *myargs[argc];
	        for (int i = 0; i < argc; i++)
	        {
	        	myargs[i] = strdup(argv[i]);
	        }
	        myargs[argc] = NULL; // marks end of array          
	        execvp(myargs[0], myargs);  // runs word count
	        printf("command not found \n");
	        exit(1);
	    } 

	    else 
	    {
	    	int wc;
	        // parent goes down this path (original process) 
	        if (amp_count ==1) // if there are no multiple commands so wait else display prompt immediately
	        {
	        	wc = wait(NULL);
	        }
	        if (amp_count > 1)
	        {
	        	insertFirst(argv[0],rc);
	        }

	        if (redir_cont>1)
	        {
	        	assert(wc >= 0);
	        }
	        //printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",rc, wc, (int) getpid());
	    }
	}
		
}

void exitShell()
{
	delDeadChild();       //before exiting shell killing all dead and alive processes both
	delAllNodes();

}

int main(int argc, char const *argv[], char ** envp)
{
	char cwd[1024]; // current working directory
	char * str_input = (char *) malloc(100 *sizeof(char));
	ssize_t buf = 0;
	int * parsedsize = (int *) malloc(sizeof(int));
	pwd(cwd, 0);
	modifyPath(cwd);
	while(1)
	{
		pwd(cwd,0);
		printf("\033[22;33m"); //change print color to yellow
		printf("HUSH@HFA : "); //print user prompt
		printf("\033[22;36m"); //change print color to cyan
		printf("%s",cwd );
		printf(": ");
		printf("\033[0m"); //reset to deault color
		if (getline(&str_input, &buf, stdin) == 0)
		{
			continue;
		}
		if(strcmp(str_input,"exit\n")==0)
		{
			exitShell();
			break;

		}
		if (strcmp(str_input,"\n")==0)
		{
			continue;
		}

		else if(strchr(str_input,'=')!= NULL)
		{

			char ** isEqualToList = parsed(str_input,"= \n",parsedsize);
			VarPath(isEqualToList[0],isEqualToList[1]);
		}
		
		else
		{
			interlude(parsedsize,str_input,cwd,envp);	
		}
	}
	
	free(str_input);
	return 0;
}
