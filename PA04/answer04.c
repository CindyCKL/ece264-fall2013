/*
 * Please fill the functions in this file.
 * You can add additional functions. 
 *
 * Hint: 
 * You can write additonal functions.
 * You can test your functions with your own input file.
 * See details in README or typing command ./pa04 in terminal after make.
 * See output format examples in any of the files in directory expected.
 * 
 * You may create additional arrays if needed.  The maximum size
 * needed is specified by MAXLENGTH in pa04.h.
 */

#include "pa04.h"
#include <stdio.h>
#include <stdlib.h>


/*
 * =================================================================
 * This function prints all partitions of a positive integer value
 * For example, if the value is 3:
 *
 * partitionAll 3
 * = 1 + 1 + 1
 * = 1 + 2
 * = 2 + 1
 * = 3
 */

void printpartition(int * array, int length);
void partition(int * array, int index, int length);

void printpartition(int * array, int length)
{
  //LOCAL VARIABLE
  int index = 0;

  //COMPUTATION
  printf("= ");
 
  for(index = 0; index < length - 1; index++)
    {
      printf("%d + ", array[index]);
    } 
  printf("%d\n", array[length - 1]);
    
}

void partition(int * array, int index, int length)
{
  //the length of the array is the same as the value of the element, if the value is 10, there is 10 elements that we can use for partition, 1,2,3,4,5,6,7,8,9
  //LOCAL VARIABLE
  int value = 0;
  if (length == 0)
    {
      printpartition(array, index);
    }
  for(value = 1; value <= length; value++)
    {
      array[index] = value;
      partition(array, index + 1, length - value);
    }
}

void partitionAll(int value)
{
  //LOCAL VARIABLE
  int array[MAXLENGTH] = {0};

  //COMPUTATION
  printf("partitionAll %d\n", value);
  partition(array, 0, value); 
  
}


/*
 * =================================================================
 * This function prints the partitions that use increasing values.
 *
 * For example, if value is 5
 * 2 + 3 and
 * 1 + 4 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 3 + 2 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */ 

//FUNCTION DECLARATION
void partitioninc(int * array, int index, int length);

void partitioninc(int * array, int index, int length)
{
  //LOCAL VARIABLE
  int value = 0;

  //COMPUTATION
      if (length == 0)
	{
	  printpartition(array, index);
	}

      for (value = 1; value <= length; value++)
	{
	  array[index] = value;
      	  if (index == 0)
	   {	  
	     partitioninc(array, index + 1, length - value);
	  }
	  if(index > 0)
	    { 
	      if(array[index - 1] < array[index])
		{
		  partitioninc(array, index + 1, length - value);
		}
	     
	    }
	}
}

 void partitionIncreasing(int value)
 {
   //LOCAL VARIABLE
     int array[MAXLENGTH] = {0};
   
   //COMPUTATION
   printf("partitionIncreasing %d\n", value);
    partitioninc(array, 0, value);
 }

/*
 * =================================================================
 * This function prints the partitions that use Decreasing values.
 *
 * For example, if value is 5
 * 3 + 2 and
 * 4 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 3 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 *
 */
void partitiondec(int * array, int index, int length);

void partitiondec(int * array, int index, int length)
{
  //LOCAL VARIABLE
  int value = 0;

  //COMPUTATIONS
  if (length == 0)
    {
      printpartition(array, index);
    }
  for(value = 1; value <= length; value++)
    {
      array[index] = value;
      if (index == 0)
	{
	  partitiondec(array, index + 1, length - value);
	}
      if (index > 0)
	{
	  if(array[index - 1] > array[index])
	    {
	      partitiondec(array, index + 1, length - value);
	    }
	}
    }
}

void partitionDecreasing(int value)
{
  //LOCAL VARIABLE
  int array[MAXLENGTH] = {0};

  //COMPUTATION
  printf("partitionDecreasing %d\n", value);
  partitiondec(array, 0, value);
  
}

/*
 * =================================================================
 * This function prints odd number only partitions of a positive integer value
 * For example, if value is 5
 * 1 + 1 + 1 + 1 + 1 and
 * 1 + 3 + 1 are valid partitions
 *
 * 5 is a valid partition
 * 
 * 1 + 1 + 1 + 2 and
 * 2 + 1 + 2 and
 * 2 + 3 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

//FUNCTION DECLARATION
void partitionodd2(int * array, int index, int length);

void partitionodd2(int * array, int index, int length)
{
  //LOCAL VARIABLES
  int value = 0;

  //COMPUTATIONS
  if (length == 0)
    {
      printpartition(array, index);
    }
  for(value = 1; value <= length; value++)
    {
      if(value % 2 == 1)
	{
	  array[index] = value;
	  partitionodd2(array, index + 1, length - value);
	}
    }
 }

void partitionOdd(int value)
{
  //LOCAL VARIABLES
   int array[MAXLENGTH] = {0};

  //COMPUTATIONS
  printf("partitionOdd %d\n", value);
   partitionodd2(array, 0, value);
}

/*
 * =================================================================
 * This function prints even number only partitions of a positive integer value
 * For example, if value is 8
 * 2 + 2 + 2 + 2and
 * 2 + 4 + 2 are valid partitions
 *
 * 8 is a valid partition
 *
 * 2 + 1 + 1 + 2 + 2and
 * 2 + 1 + 2 + 3and
 * 5 + 3 are invalid partitions.
 *
 * if the value is 5, there will be no result generated
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

//FUNCTION DECLARATION
void partitioneven2(int * array, int index, int length);

void partitioneven2(int * array, int index, int length)
{
  //LOCAL VARIABLES
  int value = 0;

  //COMPUTATIONS
  if (length == 0)
    {
      printpartition(array, index);
    }
  for (value = 1; value <= length; value++)
    {
      if ( value % 2 == 0)
	{
	  array[index] = value;
	  partitioneven2(array, index + 1, length - value);
	}
    }
}

void partitionEven(int value)
{
  //LOCAL VARIABLES
  int array[MAXLENGTH] = {0};

  //COMPUTATIONS
  printf("partitionEven %d\n", value);
  partitioneven2(array, 0, value);
}

/*
 * =================================================================
 * This function prints alternate ood and even number partitions of a positive integer value. Each partition starts from an odd number, even number, ood number again, even number again...etc.
 *
 * For example, if value is 6
 * 1 + 2 + 1 + 2 and
 * 3 + 2 + 1 are valid partitions
 *
 * 6 is not a valid partition
 *
 * 2 + 1 + 1 + 2 and
 * 2 + 1 + 3and
 * 5 + 1 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

//FUNCTION DECLARATION
void partitionboth(int * array, int index, int length);

void partitionboth(int * array, int index, int length)
{
  //LOCAL DECLARATION
  int value = 0;

  //COMPUTATIONS
  if (length == 0)
    { 
      printpartition(array, index);
    }

  for(value = 1; value <= length; value++)
    {
      if(index % 2 == 0)
	{
	  if(value % 2 == 1)
	    {
	      array[index] = value;
	      partitionboth(array, index + 1, length - value);
	    }
	}
      if(index % 2 == 1)
	{
	  if(value % 2 == 0)
	    {
	      array[index] = value;
	      partitionboth(array, index + 1, length - value);
	    }
	}
    }
}

void partitionOddAndEven(int value)
{
  //LOCAL VARIABLES
  int array[MAXLENGTH] = {0};

  //COMPUTATIONS
  printf("partitionOddAndEven %d\n", value);
  partitionboth(array, 0, value);
  
}

/*
 * =================================================================
 * This function prints prime number only partitions of a positive integer value
 * For example, if value is 6
 * 2 + 2 + 2 and
 * 3 + 3 are valid partitions
 *
 * 6 is not a valid partition
 * 
 * 2 + 4 and
 * 1 + 5 are invalid partitions.
 * 
 * The program should generate only valid partitions.  Do not
 * generates invalid partitions and checks validity before printing.
 */

void partitionlast(int * array, int index, int length);
int isitprime(int number);

void partitionlast(int * array, int index, int length)
{
  //LOCAL VARIABLE
  int value = 0;
  int check = 0;

  //COMPUTATIONS
  if(length == 0)
    {
      printpartition(array, index);
    }

  for(value = 2; value <= length; value++)
    {
      check = isitprime(value);
      if (check == 1)
	{
	  array[index] = value;
	  partitionlast(array, index + 1, length - value);
	}
    }
}

int isitprime(int number) //to test whether the value is a prime number or not
{
  //LOCAL VARIABLE
  int i;//loop control expression

  //COMPUTATIONS
  if (number > 2 && number % 2 == 0) //even number is not prime number
    {
      return -1;
    }

  for(i = 3; i < number; i += 2) //since prime number can only be divided by the number itself, it will never give you 0 when it is divided by any number that is lesser than it is, that is why it will return 1 in the end and become true!
    {
      if(number % i == 0)
	{
	  return -1;
	}
      }
  return 1;
}

void partitionPrime(int value)
{
  //LOCAL VARIABLES
  int array[MAXLENGTH] = {0};

  //COMPUTATIONS
  printf("partitionPrime %d\n", value);
  partitionlast(array, 0, value);
}
