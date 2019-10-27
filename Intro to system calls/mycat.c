#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void displayFile(int numberOfFiles, char* filesArray[])
{
	FILE *fptr;
	char filename[1000], readFile;
	for (int i = 1; i < numberOfFiles; i++)
	{
		fptr = fopen(filesArray[i], "r");
		if (fptr == NULL)
		{
			printf("No such file or directory \n");
			exit(0);
		}
		readFile = fgetc(fptr);
		while(readFile!= EOF)
		{
			printf("%c", readFile);
			readFile = fgetc(fptr);
		}
		fclose(fptr);
	}
}

void numberLines (int numberOfFiles, char * filesArray[])
{
	FILE *fptr;
	char filename[1000], readFile;
	int couter = 1;
	for (int i = 2; i < numberOfFiles; i++)
	{
		fptr = fopen(filesArray[i], "r");
		if (fptr == NULL)
		{
			printf("No such file or directory \n");
			exit(0);
		}
		readFile = fgetc(fptr);

		printf("%*d",6,couter);
		//printf("%d",couter);
		printf("  ");
		while(readFile!= EOF)
		{
			if(readFile == '\n')
			{
				printf("%c", readFile);
				couter++;
				printf("%*d",6,couter);
				printf("  ");
			}
			else
			{
				printf("%c", readFile);
			}
			
			readFile = fgetc(fptr);

		}
		printf("\n");
		fclose(fptr);
	}
}

void fromSTDIN (int argc, char* argv[])
{

	int couter = 1;
	char readFile;
	readFile = fgetc(stdin);
	if (strcmp(argv[argc -1],"-n") == 0)
	{
		printf("%*d",6,couter);
		printf("  ");
		while(readFile!= EOF)
		{
			if(readFile == '\n')
			{
				printf("%c", readFile);
				couter++;
				readFile = fgetc(stdin);
				if (readFile != EOF)
					printf("%*d",6,couter);
				printf("  ");
			}
			else
			{
				printf("%c", readFile);
				readFile = fgetc(stdin);
			}
		}
	}
	else
	{
		while(readFile!= EOF)
		{
			printf("%c", readFile);
			readFile = fgetc(stdin);
		}	
	}

}

int main (int argc,char*argv[])
{


	if (!isatty(1))
	{
		fromSTDIN(argc,argv);
	}

	else 
	{
		if (argc < 2)
		{
			printf("%s\n", "please pass a valid argument");
			exit(0);
		}
		
		if ((argc>1) && (strcmp(argv[1],"-n") == 0))
		{
			numberLines(argc,argv);
		}

		displayFile(argc,argv);
	}

}