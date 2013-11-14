#include <stdio.h>
#include <stdlib.h>
#include "pa09.h"

//can i use the same function for bytes and bits??

//WILL BE CALLED BY MAKING A TREE FUNCTION
HuffNode * HuffNode_create(int data)//will the data be int? or char?
{
  //making newnode
  HuffNode * newnode;
  newnode = malloc(sizeof(HuffNode));
  if(newnode == NULL)
    {
      printf("Error! No malloc!!");
      return NULL;
    }
  newnode -> left = NULL;
  newnode -> right = NULL;
  newnode ->value = data;

  return newnode;
}

//PUSH AND PULL CALL STACK
Stack * Stack_push(Stack * newstack, HuffNode * thenode)
{
  Stack * topstack = malloc(sizeof(Stack));
  if(topstack == NULL)
    {printf("Error! No malloc!");}
  topstack -> node = thenode; //data
  topstack -> next = newstack;
  return topstack;
}

Stack * Stack_pop(Stack * topstack)
{
  if (topstack == NULL)
    {
      return NULL;
    }

  Stack * nextstack = topstack -> next;
  free(topstack); //release stack, not tree
  return nextstack;
}

//can i use this for bytes also? or only for bits?

//MAKING A TREE, for bytes
HuffNode * makingatreewithbyte(FILE * fptr)
 {
   int treedone = 0;
   Stack * newstack = NULL; //create an empty stack
   int command;
   command = fgetc(fptr); //read the file
   while(!feof(fptr) && (treedone == 0))
     {
       if(command != '0')
	 {
	   command = fgetc(fptr); //command is the data
	   HuffNode * node = HuffNode_create(command);
	   newstack = Stack_push (newstack, node);
	 }

       if(command == '0')
	 {
	   HuffNode * node1 = newstack -> node;
	   newstack = Stack_pop(newstack);
	   if(newstack == NULL)
	     {
	       treedone = 1;
	       return node1; //you get your tree
	     }
	   else
	     {
	       HuffNode * node2 = newstack -> node;
	       newstack = Stack_pop(newstack);
	       HuffNode * par = malloc(sizeof(HuffNode));
	       par -> right = node1;
	       par -> left = node2;
	       newstack = Stack_push(newstack, par);
	     }
	 }
       command = fgetc(fptr);
     } 
   return NULL;
 }

/*
int bytetobits(unsignedchar byte, int loc)
{
}




void readdata(File * fptr, unsignedchar * data, int size, int stage)
{
  int index = 0;
  while (!feof(fptr))
    {
      unsignedchar * ch = fgetc(fptr);
      int location = 0;
unsignedchar mask = 
    }
}

void maskfunction()
  {
  }


*/

//FUNCTION TO PRINT
void Huff_postOrderPrint(HuffNode * tree, FILE * fptr)
{
    // Base case: empty subtree
    if (tree == NULL) 
      {
    return;
    }

    // Recursive case: post-order traversal

    // Visit left
    fprintf(fptr, "Left\n");
    Huff_postOrderPrint(tree->left, fptr);

    fprintf(fptr,"Back\n");

    // Visit right
    fprintf(fptr, "Right\n");
    Huff_postOrderPrint(tree->right, fptr);

    fprintf(fptr, "Back\n");
    // Visit node itself (only if leaf)
    if (tree->left == NULL && tree->right == NULL) 
      {
	fprintf(fptr, "Leaf: %c\n", tree->value);
      }
    

}

void destroy(HuffNode * head)
{
  if ( head == NULL)
    {return;}

  destroy(head->left);
  destroy(head->right);

  free(head);
}

  //return 1 or 0 of the bit in the byte based on location


// have to make a function for mask 
// function to recognize whther input is bit or byte
