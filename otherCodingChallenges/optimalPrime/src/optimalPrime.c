/*
 ============================================================================
 Name        : optimalPrime.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define maxval( _a, _b ) ( ( (_a) > (_b) ) ? (_a) : (_b) )

int mark[100];

int checkPrime(int n);

int main(void) {

	int i;

	int count = 0;

	do
	{
		checkPrime(i = 3);
		count++;
	}
	while(count != 100);

	printf("Here is the count%d", i);

	return EXIT_SUCCESS;
}

int checkPrime(int n)
{
	int i = 3, count = 0, c;
	float		t;
	time_t 		start;
	time_t 		end;
	float 		time_max	 = 0.0;


	  //printf("Enter the number of prime numbers required\n");
	  //scanf("%d",&n);

	   //if ( n >= 1 )
	   //{
	     // printf("First %d prime numbers are :\n",n);
	   //   printf("2\n");
	   //}

	start = clock();
	   while(1)
	   {

	      for ( c = 2 ; c <= i - 1 ; c++ )
	      {
	         if ( i%c == 0 ) //figure out what this for loop does :: this loops until i is a prime number, then it counts c up to equal i, then it breaks out of the loop to continue the program
	            break;
	      }
	      if(kbhit()) break;


	      if ( c == i )
	      {
	    	 end=clock();
	    	 t=(float)(end-start)/CLOCKS_PER_SEC;
	    	 time_max = maxval( t, time_max );

	         printf("\r%10d %d %f %f", count, i, t, time_max );
	         count++;
	         start=end;
	      }

	          //printf("%ld\n",t);
	      //for ( count = 2 ; count > 0 ;  )
	      i++;
	   }


	 return 0;
}
