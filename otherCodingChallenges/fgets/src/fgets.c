/*
 ============================================================================
 Name        : fgets.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE 	* pFile;
	char mystring [100];

	pFile = fopen ("myfile.txt" , "r");
	if (pFile == NULL) perror ("Error opening file");
	else {
	if ( fgets (mystring , 100 , pFile) != NULL )
	  puts (mystring);
	  fclose (pFile);
	}
	return 0;
}
