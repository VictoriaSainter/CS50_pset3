/***************************************************************************
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 ***************************************************************************/
 
// standard libraries
#define _XOPEN_SOURCE
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // Making sure the number of commandline arguments is equal to 2 or 3, otherwise throwing an error i.e. making sure n at least has been inputted
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // Letting the second commandline argument equal integer n, to take in the number of longs that need to be printed out. 
    int n = atoi(argv[1]);

    // checking if there has been an 's' value inputted - if yes, use the 3rd commandline argemuent as 's', the seed. If no, use NULL
    if (argc == 3)
    {
        //generate a sequence of pseudo-random numbers
        srand48((long int) atoi(argv[2]));
    }
    else
    {
        srand48((long int) time(NULL));
    }

    // print n random numbers 
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
