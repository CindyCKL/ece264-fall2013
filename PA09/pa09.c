#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"


int main( int argc, char ** argv)
{
FILE * fptr = NULL; //file pointer
  //CHECK ARGC  
if (argc != 3)
    {
      printf("Error! Number of arguments must be 3! ./pa09 <input file> <output file>");
      return EXIT_FAILURE;    
    }
//OPEN INPUT AND CHECK
  fptr = fopen (argv[1], "r");
  if(fptr == NULL)
    {
      printf("File error!\n");
      return EXIT_FAILURE;
    }

  //CALL FUNCTION TO CREATE HUFFMAN TREE, RETURN HEAD OF THE TREE
  HuffNode * headhuffman = NULL; 
  /*
  if(strstr(fptr, "ch") != NULL)
    {
      headhuffman = makingatreewithbyte(fptr);
    }
  else
    {
      headhuffman = makingatreewithbits(fptr);
    }
  */

  headhuffman = makingatreewithbyte(fptr);

  fclose (fptr);

  //OPEN AN OUTPUT FILE
   fptr  =fopen(argv[2], "w");
  if(fptr == NULL)
    {
      printf("output file error\n");
      return EXIT_FAILURE;
    }

  //PRINT HUFFMAN TREE
  Huff_postOrderPrint(headhuffman, fptr);


  fclose (fptr);

  destroy(headhuffman);

  return 0;

}

