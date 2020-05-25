/*
 ============================================================================
 Name        : loop.c
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
	int 	i;
	double 	u 		= 1.0;
	int 	num;
	int 	j  		= 1;
	double number, sum  = 0;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("Enter a number:\n");
	scanf("%d", &num);

		for(i = 0; i < num; i++)
		{
			u = u * 1.1;
			printf("%12.3f 0x%02x\n", u, i);
		}


		while(j <= 5 )
		{
			printf("%d\n", j);
			++j;
		}

		do
		{
			printf("Enter a number: ");
			scanf("%lf", &number);
			sum += number;
		}
		while(number != 0.0);

		printf("Sum = %.2lf", sum);


		for(i = 0; i < 10; ++i)
		{
			printf("\nEnter a number n%d: ", i);
			scanf("%lf", &number);

			if(number < 0.0)
			{
				continue;
			}

			sum += number;
		}

		printf("Sum = %.2lf", sum);



		char operator;
		double num1, num2;

		printf("Enter an operator (+, -, *, /): ");
		scanf("%c", &operator);

		printf("\nEnter two operands: ");
		scanf("%lf %lf", &num1, &num2);

		switch(operator)
		{
			case '+':
				printf("%.1lf + %.1lf = %.1lf", num1, num2, num1 + num2);
				break;

			case '-':
				printf("%.1lf - %.1lf = %.1lf", num1, num2, num1 - num2);
				break;

			case '*':
				printf("%.1lf * %.1lf = %.1lf", num1, num2, num1 * num2);
				break;

			case '/':
				printf("%.1lf / %.1lf = %.1lf", num1, num2, num1 / num2);
				break;

			default:
				printf("Error! Operator is not correct.");

		}































	return EXIT_SUCCESS;
}
