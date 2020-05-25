/*
 ============================================================================
 Name        : tempConvert.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int 	tempCelsius;
	int 	tempF;

	printf( "Enter the temperature in Celsius:\n" );
	scanf( "%d", &tempCelsius);

	tempF = (tempCelsius * (9 / 5) + 32);

	printf( "The temperature, %d Celsius, is %d Fahrenheit",tempCelsius ,tempF );



	return 0;
}
