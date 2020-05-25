/*
 ============================================================================
 Name        : aetes.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int num1, num2;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

		printf("Enter two numbers: ");
		scanf("%d %d", &num1, &num2);

		if(num1 == num2)
		{
			printf("Result: %d = %d", num1, num2);
		}
		else if(num1 > num2)
		{
			printf("Result: %d > %d", num1, num2);
		}
		else
		{
			printf("Result: %d < %d", num1, num2);
		}

		int i;

		for(i = 1; i < 10; i++)
		{
			printf("%d", i);
		}

		return EXIT_SUCCESS;




}
