/*
 ============================================================================
 Name        : stopwatch.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <time.h>
#include <conio.h>

int main()
{
	clock_t s, n;

	long int timeHr;
	long int timeMin;
	long int timeSec;
	long int timeMil;
	long int timeDis;

    printf("*#This is a stopwatch#*\n\n\n");
    printf("**Press 'p' to pause.\n");
    printf("**Press any key to start & to stop.");
    getch();
    system("cls");
    printf("\t\t*#This is a stopwatch#*\n\n\n");


    s = clock();

    while(1)
    {
    	while(1)
    	{
    		n = clock();
    		timeDis = n - s;

    		timeHr = ((((timeDis)/1000))/60)/60;
    		timeMin = (((timeDis)/1000)/60)%60;
    		timeSec = ((timeDis)/1000)%60;
    		timeMil = ((timeDis)%1000);

            printf("\r ");
            printf("Time-\t %ld hrs : %ld min : %ld sec : %ld millis ",timeHr, timeMin, timeSec, timeMil); //put in hours
            if(kbhit()) break;  //kbhit() does not read the character
        }

        if(getch()=='p')
        {
            printf("\rTime-\t %ld hrs : %ld min : %ld sec : %ld millis ",timeHr, timeMin, timeSec, timeMil);
            getch();
        }
        else break;

        s=s+(clock()-n);    //split time
        //s=clock();    //lap time
    }

    printf("\rTime-\t %ld hrs : %ld min : %ld sec : %ld millis ",timeHr, timeMin, timeSec, timeMil);

    printf("\n\n\n");

    return 0;
}

