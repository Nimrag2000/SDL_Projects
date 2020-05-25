/*
 ============================================================================
 Name        : array.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int main(void) {

	int array[3] = {6, 3, 77};

	printf("%d\n", array[2]);

	//scanf("%d", array[2]);

	printf("%d\n", array[2]);

	int marks[10], i, n, sum = 0, average;
	     printf("Enter n: ");
	     scanf("%d", &n);
	     for(i=0; i<n; ++i)
	     {
	          printf("Enter number%d: ",i+1);
	          scanf("%d", &marks[i]);
	          sum += marks[i];
	     }
	     average = sum/n;
	     printf("Average = %d", average);

	return EXIT_SUCCESS;
}
