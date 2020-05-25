/*
 ============================================================================
 Name        : binary.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int main(void) {
	int n = 0; //min value
	int x = 1000000;  //max value
	int g; //guess equation

	int i; //random number
	int num = 0;
	time_t t;
	int f = x +1;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	srand((unsigned) time(&t));

	i = rand() % f;

	/*
	 * loop until I find the number
	 * 		find halfway point vbetween min and max
	 * 		if numvber is less halfway point
	 * 			set max to halfway point
	 * 		else
	 * 			set min to halway piont
	 *
	 */
	 do
	 {
		 	g = ((x-n)/2) + n;
		 	if(i < g)
		 	{
		 		x = g;
		 		printf("The computer guessed %d, wrong.\n", g);
		 	}
		 	else if(i > g)
		 	{
		 		n = g;
		 		printf("The computer guessed %d, wrong.\n", g);
		 	}
		 	num++;
	 }
	 while(i != g);

	 printf("\nYou guessed correctly: %d", i);
	 printf("\nIt took %d tries.", num);


	/*do
	{
		printf("\nGuess a number between 1 and 100: ");
		scanf("%d", &guessNo);

		if(guessNo > answerNo)
		{
			printf("\nGuess is higher than the answer: %d.  Guess again.", guessNo);
		}
		else if(guessNo < answerNo)
		{
			printf("\nGuess is lower than the answer: %d.  Guess again.", guessNo);
		}
	}
	while(guessNo != answerNo);

	printf("\nYou guessed correctly: %d", guessNo);*/











	/*if(guessNo > answerNo)
	{
		printf("Guess is higher than the answer: %d.  Guess again.", guessNo);
		scanf("%d", &guessNo);
	}
	else if(guessNo < answerNo)
	{
		printf("Guess is lower than the answer: %d.  Guess again.", guessNo);
		scanf("%d", &guessNo);
	}
	else if(guessNo == answerNo)
	{
		printf("You guessed correctly: %d", guessNo);
		scanf("%d", &guessNo);
	}*/









	return EXIT_SUCCESS;
}
