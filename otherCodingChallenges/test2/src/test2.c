/*
 ============================================================================
 Name        : test2.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>


int addNumbers(int a, int b);

void display();


int main(void)
{

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	int n1,n2,sum;

	printf("Enters two numbers: ");

	scanf("%d %d",&n1,&n2);

	sum = addNumbers(n1, n2);        // function call

	printf("sum = %d",sum);

	display();
	display();



	return EXIT_SUCCESS;
}

int addNumbers(int a,int b)         // function definition
{
    int result;

    result = a+b;

    return result;                  // return statement
}

void display()
{
    static int c = 0;
    printf("%d  ",c);
    c += 5;
}
