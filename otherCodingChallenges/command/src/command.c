/*
 ============================================================================
 Name        : command.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	char name[100];
	int grade;
	int total;
}assignment_type;

int main( int argc, char *argv[] )
{
	int 		i;
	int			rows		= 0;
	FILE      * pFile;
	char		aLine[100];
	char	  * ptr			= NULL;
	int			sumGrade	= 0;
	int 		sumTotal	= 0;
	assignment_type	assignment[100];


	for(i = 1; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}




	//printf( "Enter a number: \n" );
	//fgets(aLine, 20, stdin);
	//i = atoi (aLine);
	//printf( "The value entered is %d.  Its double is %d\n", i, i * 2 );

	//pFile = fopen ("test.csv","w");
	//if (pFile != NULL)
	//{
		//fputs ("2? 2? 2? 2? 2? 2? 2? 2? 2? 2? 2? 2?", pFile);
		//fclose (pFile);
	//}

	if(argc <= 1)
	{
		printf("no filename given\n");  //this if tells you to give a file name if you dont put one in the ./command.exe
		return -1;
	}

	pFile = fopen(argv[1], "r");
	if(pFile == NULL)
	{
		printf("no files exist\n");   //this if tells you nothing exists if you put in something that doesnt exist
		return -2;
	}

	//fseek( pFile, 9, SEEK_SET );

	while( !feof(pFile) )
	{
		ptr = fgets(aLine, 100, pFile);
		if( ptr == NULL )
		{
			break;
		}

		ptr = strtok( ptr, ",");
		//^put assignment_name here
		strcpy( assignment[rows].name, ptr );

		ptr = strtok( NULL, "," );
		//^put asssignment_grade here
		assignment[rows].grade = atoi( ptr );

		ptr = strtok( NULL, "," );
		//^put assignment_total here
		assignment[rows].total = atoi( ptr );

		rows++;




  		//ptr = strtok( NULL, "," );



	}

	for( i = 0; i < rows; i++ )
	{
		printf( "%s\t %i\t %i\n", assignment[i].name, assignment[i].grade, assignment[i].total );
		sumGrade += assignment[i].grade;
		sumTotal += assignment[i].total;
	}
	printf( "Avg Grade is %f\n", (float)sumGrade / (float)sumTotal );

	fclose(pFile);



	return 0;
}
