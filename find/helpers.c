/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
  */
  

 bool binarySearch(int value, int values[], int n) {
        int min = 0;
        int max = n;
        bool outcome = true;
        
        while (max >= min) {
        
            int mid = ((min + max)/2);
            if (values[mid] ==value) {
                
                return true;
            }
            else if (values[mid] > value){
                max = mid - 1;
                outcome = false;
            }
            else {
                min = mid + 1;
                outcome = false;
            }
        
        }
        return outcome;
}


bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    bool outcome = false;
    
    

    if (value < 0) {
    
        return outcome;
    }
    else {
        outcome = binarySearch(value, values, n);
        return outcome;
    }
}
  


/**
 * Sorts array of n values.
*/


void sort(int values[], int n)
{    
   int i, j, temp;

   for (i = 1; i < n; i++) {
      for (j = 0; j < n - 1; j++) {
         if (values[j] > values[j + 1]) {
            temp = values[j];
            values[j] = values[j + 1];
            values[j + 1] = temp;
         }
      }
 
   }

    return;
}

