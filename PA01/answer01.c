/*
 * Please fill the functions in this file.
 */
#include <stdio.h>
#include <stdlib.h>
#include "pa01.h"

/* == Note 1 :: C does not initialize variables for you ==
 *
 * Please keep in mind that C does not initialize variables.
 *
 * int sum; 
 *
 * is different from
 *
 * int sum = 0;
 *
 * The value of sum is undefined (garbage) in the first case.
 */

/* == Note 2 :: Arrays are zero-indexed  ==
 *
 * If an array has "length" elements, then valid indices are between 0
 * and length - 1, not between 1 and length. Thus, array[length] will
 * access an invalid memory location and probably crash the program.
 */

/* addElement: sums the elements of an array of integers

   Parameters:

   array: an array of integers
   length: the length of the array (i.e. the number of elements)
   
   Returns:

   This function returns the sum of the elements.
   For example, if
   array[0] is 3
   array[1] is 11
   array[2] is 9
   and length is 3
   This function should return 3 + 11 + 9 = 23.

   If the array has no elements (length is 0), then the function returns 0.
*/
int addElement(int * array, int length)
{    
  //LOCAL VARIABLES
  int sum = 0;
  int lcv;

  //COMPUTATIONS
  if (length > 0)
    {
      for (lcv = 0;lcv < length; lcv++)
	{
	  sum += array[lcv];
	}
    }
  else
    {
      sum = 0;
    }

  return (sum);
}
/*
 * =================================================================
 */
/* countNegative: how many negatives values there are in an array

   Parameters:

   array: an array of integers
   length: the length of the array (i.e. the number of elements)

   Returns:

   This function returns the number of negative elements in the array
   For example, if
   array[0] is -3
   array[1] is 11
   array[2] is -9
   array[3] is 0
   and length is 4
   This function should return 2.
   0 is not considered to be a negative number.
*/
int countNegative(int * array, int length)
{
  //LOCAL VARIABLES
  int negative = 0;
  int lcv;
  //COMPUTATIONS
  for(lcv = 0; lcv < length;lcv++)
    {
      if(array[lcv] < 0)
	{
	  negative++;
	}
    }
  return(negative);
}
/*
 * =================================================================
 */
/* isIncreasing: Is an array of integers always increasing?

   Parameters:

   array: an array of integers
   length: the length of the array (i.e. the number of elements)
  
   Returns:

   This function returns 1 if the elements are increasing
   (i.e. array[i] < array[j] for all 0 <= i < j < length).  If the
   elements are not increasing, this function returns 0.

   If the array has only one element (i.e. length is 1), the function
   returns 1.  If the array has no elements (length is 0), the function
   also returns 1.

   Examples:

   If
   array[0] is 3
   array[1] is 9
   array[2] is 11
   and length is 3
   This function should return 1
   
   If 
   array[0] is 3
   array[1] is 11
   array[2] is 9
   and length is 3
   This function should return 0

   If 
   array[0] is 3
   array[1] is 3
   array[2] is 9
   and length is 3
   This function should return 0

*/
int isIncreasing(int * array, int length)
{
  //LOCAL VARIABLES
  int increase = 0;
  int final = 0;
  int sum = 0;
  int i;

  //COMPUTATIONS
  for(i = 0; i < (length - 1); i++) //length - 1 so the last element compared is still within the array not garbage value
    {
      if(array[i] < array[i+1])
	{
	  increase = 0; //if the array is increasing, increase = 0
	}
      else
	{
	  increase = 1;
	}
      sum += increase; //if the array keeps increasing, sum == 0
    }
  if(sum == 0) //array increases
    {
      final = 1;
    }
  else //if sum > 0 that means array decreases 
    {
      final = 0;
    }
    
  return (final);
}
