
#include "pa10.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define TRUE 1
#define FALSE 0

/**
 * Returns a pointer to a new empty stack.
 */
Stack * Stack_create()
{
  Stack * newstack = malloc(sizeof(Stack));
  ListNode * node = malloc(sizeof(ListNode));
  node -> value = 1; //what should we intialize it with?
  node -> next = NULL;
  newstack -> list = node;

  return newstack;  
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you _must_ free the entire contained linked-list.
 * Also, you must safely to _nothing_ if stack == NULL. 
 */

void Stack_destroyhelper(ListNode * node);
void Stack_destroy(Stack * stack)
{
  if(stack == NULL)
    {
      return;
    }

  Stack_destroyhelper(stack->list);
  if(stack->list == NULL)
    {
      free(stack);
      return;
    }    
}

void Stack_destroyhelper(ListNode * node)
  { 
    if(node == NULL)
      {
      return;
    }
  ListNode * nextnode = node->next; //saving the address of the next node that stack has
  Stack_destroyhelper(nextnode);
  free(node); //free the node stack ponts now //make stack poitns to th nextnode
 //destroying the next node
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if (stack->list == NULL)
    {return TRUE;}
  return FALSE;

}


/**
 * Pop the front 'value' from the stack.
 *
 * More precisely, this function must do two things:
 * (1) Return the value of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 */
int Stack_pop(Stack * stack)
{ 
  if (stack->list == NULL)
    {
      return -1;
    }
  int value = stack->list->value;
  ListNode * nextnode = stack->list->next;
  free(stack->list);
  stack->list = nextnode;
    return value;
}

/**
 * Push an 'value' onto the front of the stack.
 *
 * More precisely, this function must:
 * (1) Create a new ListNode with 'value' for it's value.
 * (2) Push that new ListNode onto the front of the stack's list.
 */
void Stack_push(Stack * stack, int value)
{
  if(stack->list == NULL)
   {
     return;
   }
  ListNode * node1 = malloc(sizeof(ListNode));
  node1->value = value;
  node1->next=stack->list;
  stack->list = node1;

}

/**
 * Sort 'array' of length 'len' using Donald Knuth's "StackSort"
 *
 * To do this, you must implement the following pseudo-code:
 * (1) Maintain a 'write_index'. This is where you'll write values to
 *     as you sort them. It


 starts off as zero.
 * (2) Initialize an empty stack
 * (3) For each input value 'x':
 *     (3.a) While the stack is nonempty and 'x' is larger than the 
 *           front 'value' on the stack, pop 'value' and:
 *           (3.a.i) Write 'value' to array[write_index], and 
 *                   increment write_index.
 *     (3.b) Push x onto the stack.
 * (4) While the stack is nonempty, pop the front 'value' and follow
 *     step (3.a.i).
 *
 * The output should be a sorted array if, and only if, the array
  * is stack-sortable. You can find files full of stack-sortable and
 * stack-unsortable arrays in the 'expected' folder.
 */
void stackSort(int * array, int len)
{
  int write_index = 0;
  int i = 0;
  int number = 0;
  int value = 0;
  Stack * newstack = Stack_create();

  for(i = 0; i<len; i++)
    {
       number = array[i];
      //   printf("number %d\n", number);
      
      while((newstack->list != NULL) && (number > (newstack->list->value)))
	{
	  value =  Stack_pop(newstack);
	  //if(value>0)
	    array[write_index] = value;
	      (write_index)++;
	  Stack_push(newstack, number); 
	}
      Stack_push(newstack, number);
    }
 
while(newstack->list != NULL)
	  {
	    value = Stack_pop(newstack);
	    array[write_index] = value;
	    (write_index)++;
	  }

  for(i=0; i<len; i++)
    {
      printf("%d\n", array[i]);
    }

}

/**
 * Return TRUE (1) if the 'array' of length 'len' is stack-sortable.
 *
 * To do this you must:
 * (1) If 'len' is less than 3, return TRUE.
 * (2) Find the maximum value in 'array'.
 * (3) Partition array into two parts: left of max, and right of max.
 * (4) The maximum value in left must be smaller than the minimum
 *     value in right. (Otherwise return FALSE.)
 * (5) Return TRUE if both left and right are stack-sortable.
 *
 * The 'expected' directory contains files for all sortable and 
 * unsortable sequences of length len. You must return TRUE for every
 * sequence in the sortable files, and you must return FALSE for every
 * sequence in the unsortable files.
 */

int partition(int * array, int start, int end);

int isStackSortable(int * array, int len)
{
  int sortable = partition(array, 0, len);
  return sortable;
}

int partition(int * array, int start, int end)
{
  if((end-start) < 3)
    {
      return TRUE;
    }

  int indexmax = start; //declaring the indexmax as the first index, since its a recursive function, start is not always zero so we cant use zero
  int i;
  int max = array[start]; //declaring the first element in the array as the maximum then compare them afterwards, again its a recursive function so cant use zero

  for(i = start; i < end; i++) //i<= end because we already use length-1 as an argument (check isStackSortable function)
    {
      if(array[i] > max)
	{
	  max = array[i];
	  indexmax = i;
	}
    }

  int maxleft = array[start]; 
  int indexmaxleft = start;
  if(indexmax == start)
    {
      maxleft = -1;
    }
  else
    {
      for(i = 0;i < indexmax; i++) //i stops before indexmax because it does not take indexmax value into account
	{
      if(array[i] > maxleft)
	{
	  maxleft = array[i];
	  indexmaxleft = i;
	}
	}
    }

  int minright = array[indexmax + 1];
  int indexminright = indexmax + 1;
  if(indexmax == (end-1)) 
    {
      minright = array[indexmax];
    }
  else
    { 
      for(i = indexmax + 1; i < end; i++)
	{
      if(array[i] < minright)
	{
	  minright = array[i];
	  indexminright = i;
	}
    }
    }

  int left = FALSE;
  int right = FALSE;
  if(maxleft == -1)
    {
      left = TRUE;
      right = partition(array, indexmax + 1, end);
    }
  else if(minright == array[indexmax])
    {
      left = partition(array, 0, indexmax);
      right = TRUE;
    }
  else if (maxleft < minright)
    {
      left = partition(array, start, indexmax);
      right = partition(array, indexmax+1, end);
    }

  if((left == TRUE) && (right == TRUE))
    {
      return TRUE;
    }
 
return FALSE;

}

/**
 * Generates (and prints) all the unique binary tree shapes of size k
 *
 * To do this, you must:
 * (1) Create an array with the elements [1..k] inclusive.
 * (2) Find all the permutations of this array.
 * (3) In the base-case of your permute function, you must test if the
 *     permutation is "stack-sortable"
 * (4) If the permutation is "stack-sortable", then build a binary
 *     tree, and print it using the "Tree_printShape(...)" function.
 *
 * Your genShapes() function must NOT produce duplicate tree shapes.
 * The correct outputs for sizes [1..9] are in the 'expected' 
 * directory.
 */


void swap(int * a, int * b);
void permutehelper(int * array, int index, int length);
void permute(int * array, int length);

void genShapes(int k)
{
  int * array;
  array = malloc(sizeof(int)*k);
  int i=0;
  for(i = 0; i < k; i++)
   {
      array[i] = i;
      //    printf("array[%d] = %d\n", i, array[i]);
    }

  permute(array, k);
  //printf
  return;
}

void swap(int * a, int * b)
{ 
  int t = (*a);
  (*a) = (*b);
  (*b) = t;
}

void permutehelper(int * array, int index, int length)
{
   if(index == length)
    {
      int sortable = isStackSortable(array, length);
      if(sortable == TRUE)
	{
	  TreeNode * root =  Tree_build(array, length);
	  Tree_printShape(root);
	  Tree_destroy(root);
	  return;
	}
      else
	{return;}
    }

  int pos;

  for(pos = index; pos < length; pos++)
    {
      swap(&array[pos], &array[index]);
     permutehelper(array, index + 1, length);
      swap(&array[pos], &array[index]);
    }

}

void permute(int * array, int length)
{
  permutehelper(array, 0, length);
  return;
}


//#ifndef TEST01
//#define LENGTH 2
//int main(int argc, char ** argv)
//{
  //int i;
  //int k = 3;
  //genShapes(k);
  //printf("%c", sortable);
  /* Stack * newstack = Stack_create(); */
  /* printf("newstackk %p\n", newstack); */
  /* printf("newstacl->list %p\n", newstack->list); */
  /* printf("newstack->list->next %p\n", newstack->list->next); */
  /* printf("newstack list value %d\n", newstack->list->value); */
  /* Stack_destroy(newstack); */
  /* //printf("newstackk %s\n", newstack); */
  /* int empty = Stack_isEmpty(newstack); */
  /* printf("empty %d\n",empty */  

//printf("newstacl->list %p\n", newstack->list);
/*   int array[LENGTH]= {0}; */
/*   for(i=0; i<LENGTH; i++) */
/*     { */
/*       array[i] = i+1; */
/*         printf("%d\n", array[i]); */
/*     } */

/*   stackSort(array,LENGTH);  */
/*   return 0; */
/* }*/

//return 0;
//}


