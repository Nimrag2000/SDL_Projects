/*
 ============================================================================
 Name        : test.c
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
	int 	my_var;


	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	printf( "This is a new line. See, it's a new line!\n" );
	my_var = 0;
	printf( "%d", my_var );

	if (my_var == 0)
	{
		printf( "zero!\n" );
	}

	int number;

	printf("Enter an integer: ");
	scanf("%d", &number);

	if(number % 2 == 0)
	{
		printf("%d is an even number:", number);
	}
	else
	{
		printf("%d is an odd number: ", number);
	}

	int num1, num2;

	printf("\nEnter two numbers: ");
	scanf("%d %d", &num1, &num2);

	if(num1 == num2)
	{
		printf("\nResult: %d = %d", num1, num2);
	}
	else if(num1 > num2)
	{
		printf("Result: %d > %d", num1, num2);
	}
	else
	{
		printf("Result: %d < %d", num1, num2);
	}



	int num, count, sum = 0;

	printf("\nEnter a pos integer: ");
	scanf("%d", &num);

	for(count = 1; count <= num; ++count)
	{
		sum += count;
	}

	printf("Sum = %d", sum);

	int u = 1;

	while(u <= 5)
	{
		printf("%d\n", u);
		++u;
	}

	return EXIT_SUCCESS;
	}
