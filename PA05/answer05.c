#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa05.h"

/*
 * Read a file of integers.
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of integers (one
 * per line)
 * 
 * numInteger: pointer to store the number of integers in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of integers from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fscanf
 *
 * You do NOT know how many integers are in the file until you have
 * read it. Once you know how many integers there are, you can modify
 * the "numberOfIntegers" variable. (Note that this is a pointer, not
 * an integer) You must allocate memory to store the integers.
 * 
 * Once memory is allocated to store the integers, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read integeres is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of integers in the file.  For example, if
 * you write this
 *
 * int array[10000];
 * 
 *
 */

int * readInteger(char * filename, int * numInteger)
{
  FILE * fptr; //pointer to a file
  int * arr; //array that will store the integers
  int val; //one integer read
  int i; //loop control expression

  //opening the file and read it
  fptr = fopen(filename, "r");

  //if fopen fails
  if(fptr == NULL)
    {
      return NULL;
    }

  //find out how many spaces we need for the array
  while(fscanf(fptr, "%d", &val) == 1)
    {
      (*numInteger)++;
    }

  //assigning the appropriate amount of array spaces
  arr = malloc((*numInteger) * sizeof(int));


  //go back to the beginning
  fseek(fptr, 0, SEEK_SET);

  for(i = 0; i < *numInteger; i++)
    {
      fscanf(fptr, "%d", &val); //reading the integers again
      arr[i] = val; //assign values to the array
    } 

  //arr[numInteger] = "\0";
  //close the connection
  fclose(fptr);  
return arr;
}

/* ----------------------------------------------- */

/*
 * Read a file of strings. This is similar to readInteger. However,
 * each string is an array of characters. The function needs to
 * allocate memory for an array of strings, i.e., array of arrays of
 * characters. In other words, this is a two-dimensional array (thus,
 * char **).
 *
 * Arguments:
 *
 * filename: the name of a file that contains a list of strings (one
 * per line)
 * 
 * numString: pointer to store the number of strings in the
 * file. You need to update the value stored at the address which is
 * the pointer's value.  If the function fails to update the value, it
 * is considered reading the file has failed.
 *
 * Returns:
 *
 * a array of strings from the file, or NULL if *any* error is
 * encountered.
 *
 * Hint: use fgets. 
 * 
 * Remember that an array of strings is a two-dimensional array of
 * characters
 *
 * You do NOT know how many strings are in the file until you have
 * read it. Once you know how many strings there are, you can modify
 * the "numberOfStrings" variable. (Note that this is a pointer, not
 * an string) You must allocate memory to store the strings.
 * 
 * Once memory is allocated to store the strings, you will need to
 * re-read the values from the file. To do this, you must reset the
 * file pointer to the beginning of the file using the function
 * "fseek". 
 *
 * You should not use rewind (if you have learned it somewhere).  The
 * difference of rewind and fseek is that rewind does not tell you
 * whether it fails.  
 *
 * One way to read stringes is to use the "fscanf" function.  It is
 * easier than reading one character at a time by using fgetc.
 *
 * You must use malloc in this function.
 * 
 * Some old books encourage readers to type cast in front of malloc,
 * something like
 *
 * int * ptr = (int *) malloc(sizeof(int) * size);
 *
 * Type cast is no longer needed and in fact is discouraged now.  You
 * should *NOT* type cast malloc.  It is discouraged even though it is
 * not wrong.
 *
 * You will receive zero if you allocate a large array whose size is
 * independent of the number of strings in the file.  For example, if
 * you write this
 *
 * char array[10000];
 * 
 *
 */

char * * readString(char * filename, int * numString)
{
  FILE * fptr; //file pointer
  char * (* arrstring); //array contains pointers of strings
  int ind = 0; //position of the array index
  char temporary[MAXIMUM_LENGTH]; //what size should i put here? numstring = 0 initially 

  fptr = fopen(filename, "r");
  if(fptr == NULL)
    {
      return NULL;
    }

  while(fgets(temporary, MAXIMUM_LENGTH, fptr) != NULL)
    {
      (*numString)++;
    }

  //ARRAY OF POINTERS
  arrstring = malloc((*numString)*sizeof(char*));

  //GO BACK TO THE BEGINNING
  fseek(fptr, 0, SEEK_SET);

  while(fgets(temporary, MAXIMUM_LENGTH, fptr) != NULL)
    {
      arrstring[ind] = malloc(sizeof(char) * (strlen(temporary) + 1));
      strcpy(arrstring[ind], temporary); //is it *arrString[ind]?
      ind++;
    }

  fclose(fptr);
  return arrstring;

}

/* ----------------------------------------------- */
/*
 * print an array of integers, one integer per line
 */
void printInteger(int * arrInteger, int numInteger)
{
  //LOCAL VARIABLE
  int i; //loop control variable

  //PRINTING THE INTEGERS ONE BY ONE
  for(i = 0; i < numInteger; i++)
    {
      printf("%d", arrInteger[i]);
    }

}

/* ----------------------------------------------- */
/*
 * print an array of strings, one string per line
 *
 * Hint: printf("%s" ... can print a string
 */

//void fprintstring(FILE * fout, char * * arrString, int numString);

void printString(char * * arrString, int numString)
{
  int i;

  //PRINTING THE ARRAY OF POINTERS
  //  fprintstring(stdout, arrString, numString);
  for(i = 0; i < numString; i++)
    {
      if(i==0)
	{
	  printf("%s\n", arrString[i]);
	}
      else
	{
	  printf("%s", arrString[i]);
	}
    }
}
/*
void fprintstring(FILE * fout, char * * arrString, int numString)
{
  int i;

  for(i = 0; i < numString; i++)
    {
      if(i == 0)
	{
	  printf("%s\n", arrString[i]);
	}
      else
	{
	  printf("%s", arrString[i]);
	}
    }
} 
*/
/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of integers
 */
void freeInteger(int * arrInteger, int numInteger)
{
  free(arrInteger);
}

/* ----------------------------------------------- */
/*
 * release the memory occupied by the array of strings
 *
 * Hint: an array of strings is a two-dimensional array of characters
 */
void freeString(char * * arrString, int numString)
{
  int ind;

  for(ind = 0; ind < numString; ind++)
    {
      free(arrString[ind]); //should i put one star?
    }
  free(arrString);
}

/* ----------------------------------------------- */
/*
 * Write integers to a file, one integer per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrInteger: an array of integers
 * numInteger: the number of integers 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %d
 *
 */

int saveInteger(char * filename, int * arrInteger, int numInteger)
{
  FILE * fout;
  int i;
  fout = fopen(filename, "w");

  if(fout == NULL)
    {
      return 0;
    }

  for(i = 0; i < numInteger; i++)
    {
      fprintf(fout, "%d\n", arrInteger[i]);
    }

  fclose(fout); 
  return 1;
}

/* ----------------------------------------------- */
/*
 * Write strings to a file, one string per line
 *
 * Arguments:
 *
 * filename: the name of a file.
 * arrString: an array of strings
 * numString: the number of strings 
 *
 * Returns:
 * 1 if saving to the file successfully
 * 0 if *any* error is encountered
 *
 * Hint: use fprintf(... %s
 *
 */

int saveString(char * filename, char * * arrString, int numString)
{
  FILE * fout;
  int i;  
  fout = fopen(filename, "w");

  if(fout == NULL)
    {
      return 0;
    }

  // fprintstring(fout, arrString, numString);
  for(i = 0; i < numString; i++)
    {
      if(i == 0)
	{
	  fprintf(fout, "%s\n", arrString[i]);
	}
      else
	{
	  fprintf(fout, "%s", arrString[i]);
	}
    }

  fclose(fout);

  return 1;
}

/* ----------------------------------------------- */
/*
 * sort an arry of integers by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 */

int compint(const void * P1, const void * P2);

void sortInteger(int * arrInteger, int numInteger)
{
  qsort(&arrInteger[0], numInteger, sizeof(int), compint);
}
 
int compint(const void * P1, const void * P2)
{
  //DECLARING THE TYPE OF THE POINTERS
  int * intp1 = (int*) P1;
  int * intp2 = (int*) P2;

  //COPYING THE VALUES OF P1 AND P2
  int intv1 = *intp1;
  int intv2 = *intp2;

  //COMPARE THEM
  if(intv1 < intv2)
    {
      return -1;
    }

  if(intv1 == intv2)
    {
      return 0;
    }

  return 1;
} 

/* ----------------------------------------------- */
/*
 * sort an arry of strings by calling the built-in qsort function in
 * the C library.  You need to provide the comparison function. Please
 * read the Linux manual about qsort
 *
 * Hint: use strcmp in the comparison function
 *
 */

int compstring(const void * p1, const void * p2);

void sortString(char * * arrString, int numString)
{
  qsort(&arrString[0], numString, sizeof(char*), compstring);
}

int compstring(const void * p1, const void * p2)
{
  int compare;

  char * (* strp1) = (char* *) p1;
  char * (* strp2) = (char* *) p2;

  char * str1 = * strp1;
  char * str2 = * strp2;

  compare = strcmp(str1, str2);

  return compare;
}

