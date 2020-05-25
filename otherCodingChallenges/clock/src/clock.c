/* clock example: frequency of primes */
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

int main ()
{
  clock_t 	t;
  int 		f;
  time_t 	start;
  time_t 	end;
  int		i;
  int 		v;

  printf("Current clock is %ld\n", clock());
  t = clock();
  printf ("Calculating...\n");
  f = frequency_of_primes (99999);
  printf ("The number of primes lower than 100,000 is: %d\n",f);
  t = clock() - t;
  printf ("It took me %ld clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);


    start=clock();
    for( i = 0; i < 1000000000; i++ )
    {

    }
    end=clock();
    t=(end-start)/CLOCKS_PER_SEC;
    printf("%ld\n",t);

    //printf("Start your timers\n");

        /* start the time and run for 10 seconds */
        //start_timer(10);

        //int i = 0;
        /* do some work */
        //for(i = 0; i < 1000; i++){}

        /* Check and display current time */
        //printf("Current time: %d\n", current_time());

    time_t timer;
      struct tm y2k = {0};
      double seconds;

      y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
      y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

      time(&timer);  /* get current time; same as: timer = time(NULL)  */

      seconds = difftime(timer,mktime(&y2k));

      printf ("%.f seconds since January 1, 2000 in the current timezone", seconds);



  return 0;


}

