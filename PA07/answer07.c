
#include "pa07.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Prints a linked-list "head" into the output fie "out"
 *
 * NOTE: we have given the code for this function
 */
void List_print(FILE * out, Node * head)
{
 while(head != NULL)
	{
	    fprintf(out, "%5d: %6d\n", head -> index, head -> value);
	    head = head -> next;
	}
    printf("\n");
}


/**
 * Please fill in the code below
 */

/**
 * Destroys a linked list.
 * Arguments:
 * head    A pointer pointing to the first element of the linked list.
 *
 * Returns:
 * void
 *
 * Destroys (frees memory for) the whole linked list. 
 * You can either use recursion or a while loop.
 */
void List_destroy(Node * head)
{
  while (head != NULL)
    {
      Node * p = head -> next;
      free(head);
      head = p;
    }

}

/**
 * Create and initialize a linked list. 
 *
 * Arguments:
 * value     The "value" of the new node
 * index     The "index" of the new node
 *
 * Returns:
 * Returns a newly constructed node. The node can be the head of a
 * linked list.
 * 
 * You should allocate memory in this function. 
 */
Node * List_create(int value, int index)
{
  Node * mynode = malloc(sizeof(Node));
  mynode -> value = value;
  mynode -> index = index;
  mynode -> next = NULL;
  return mynode;
}

/**
 * Build a sparse array from the given indices and values with 
 * specific length.
 *
c * Arguments:
 * value    Array of values
 * index    Array of indices
 * length   Length of the above arrays
 *
 * Returns:
= * A sparse array.
 *
 * If a sparse array node has { value = 1000, index = 2 }, then that means that
 * the index "2" caries the value "1000". This is meant to convey an array of 1000 
 * "2s", but instead of creating 1000 nodes in your linked list, you only create
 * 1 node, and that note conceptually has 1000 "copies" of it. Hence 
 * each node in a sparse array has a "value" in addition to its "index".
 *
 * Note that an index can never carry the value of "0", because this would not make
 * any sense; however, negative values are fine. A negative value may seem odd
 * at first blush; however, this is like substraction, and makes sense for certain
 * cases.
 *
 * You need to insert nodes in ascending order by index.
 * See the notes to "List_insert_ascend"
 */
Node * List_build(int * value, int * index, int length)
{
  Node * head =  NULL;
  int i;
  //int j;
  for(i= 0; i < length; i++)
    {
      if(value[i] != 0)
	{
	  head = List_insert_ascend(head, value[i], index[i]);
	  //  List_print(stdout, head);
	  //printf("this is the address: %p", head->next);
	}
    }
  return head;
}


/**
 * Inserting "value" and "index" into the correct location in the 
 * sparse array "head"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the linked list.
 * value     The "value" of the value
 * index     The "value" of the index
 *
 * Returns:
 * A sparse array
 *
 * This function inserts the node ["value", "index"] into the sparse
 * array "head", and ensures that the nodes remain in ascending order
 * by their "index".
 *
 * Before and after the call to this function, "head" must be in
 * ASCENDING order by the "index" of each node.
 */
Node * List_insert_ascend(Node * head, int value, int index)
{
  if(head == NULL)
    { 
      return List_create(value, index);
    }
  if((head -> index) > index)
    {
      Node * temp;
      temp = List_create(value,index);
      temp -> next = head;
      return temp;
    }
  if((head -> index) == index)
    {
      head -> value += value;
      return head;
    }
  head -> next = List_insert_ascend(head -> next, value, index);
  return head;
}


/**
 * This function deletes the node with the passed "index"
 * 
 * Arguments: 
 * head      A pointer pointing to the first element of the sparse array.
 * index     The index to be deleted
 *
 * Returns: 
 * A sparse array with the node removed (the one with index)
 *///deletes all the index that is passed
Node * List_delete(Node * head, int index)
{
  Node * p = head;
  if(p == NULL)
    {
      return p;
    }
  //delete the first node
  if((p -> index) == index)
    {
      p = p->next;
      free(head);
      return p;
    }
  //not deleting the first node
  Node * q = p -> next; //assigning q the next p
  while((q!= NULL) && ((q->index)!= index)) //check if q is not null and not the first index
    {
      //check if q is NULL before checking the index
      p = p -> next; 
      q = q -> next;
    }

  if(q != NULL )
    {
      p->next = q->next;
      free(q);
    }
  return head;
}

/**
 * Copy a list
 *
 * Arguments:
 * head      A pointer pointing to the first element of the sparse array
 *
 * Returns:
 * A copy sparse array
 *
 * This function will copy the sparse array that is passed to it. The
 * copy will be made into new memory. 
 *
 * This is useful, for example, when we want to merge
 * two linked lists together. We can make a copy of one of the linked
 * lists, and then merge the second into the copy. In this way the
 * original copy of the list is not "mutated".
 */;
Node * List_copy(Node * head)
{
  Node * headcopy;
  if(head == NULL)
    {
      return NULL;
    }
  else
    {
      headcopy = List_create(head->value, head->index);
      headcopy -> next = List_copy(head -> next);
    }
      //can i do this?
  // headcopy = List_create(head->value, head->index);
  //  headcopy -> next = head -> next;      
  //  head = head -> next;
  // }
    return headcopy;
}


/**
 * Merged two linked list together
 * 
 * Arguments:
 * head1      A pointer pointing to linked list 1
 * head2      A pointer pointing to linked list 2
 *
 * Returns:
 * A merged sparse array
 *
 * This function will merge two linked lists. Before merging, you 
 * should make a copy of "head1" so that you will still have the 
 * original array while modifying (merging) the second linked list. 
 *
 * Please refer to the README file for detailed instructions on how to
 * merge two lists.
 *
 * This function should not modify either "head1" or "head2". You only
 * need to make a clone of "head1".
 */
Node * List_merge(Node * head1, Node * head2)
{
  Node * headcopy = NULL;
  headcopy = List_copy(head1);
  //Node * head1copy = List_copy(head1);//why is it unused?
  while(head2 != NULL)
    {
      if(head2->value != 0)
	{
      /*
      if((headcopy -> index) == (head2 -> index))
	{
	  //Node * headmerged =, should i make a new variable headmerged? 
	  headcopy->value = (headcopy->value) + (head2->value);
	  if ((headcopy -> value) == 0)
	    {
	      List_delete(headcopy, (headcopy->index));
	    }
	}
      else if (headcopy->index != head2->index)
	{
	  if(head2->value != 0)
	    {
	      headcopy = List_insert_ascend(headcopy, head2->value, head2->index);
	    }
	  //headcopy->next = List_create(head2->index, head2->
	  //if((headcopy->value) == 0)
	  //  {
	  //    List_delete(headcopy, headcopy->index);
	  //  }
	}
      
      else if(head2 == NULL)
	{
	  headcopy = List_copy(head1);
	  if(headcopy->value == 0)
	    {
	      List_delete(headcopy, headcopy->index);
	    }
	}
      */
	  headcopy = List_insert_ascend(headcopy, head2->value, head2->index);
	  if(headcopy->value == 0)
	    {
	      headcopy = List_delete(headcopy, headcopy->index);
	    }
	}      
      //head1 = head1 ->next;
      head2 = head2 ->next;
    }

    return headcopy;
}

#ifdef MYTEST
int main (int argc, char * argv[])
{
  printf("make a node and print it");
  Node * test = List_create(5,1);
  List_print(stdout, test);

  printf("destroying it");
  List_destroy(test);
  List_print(stdout, test);
  
  printf("linkingit again");
  Node * newnode =NULL;
  Node * newnode2 = NULL;
  int values[4] = {2,3,1,2};
  int indexs[4] = {1,4,2,3};
  // int i;
  int length = 4;
  printf("this is newnode");
  newnode = List_build(values, indexs, length);
  //printf("this is the newnode");  
  //List_print(stdout, newnode);

  //printf("address:%p", newnode->next);
  //printf("address:%p", newnode->next->next);
  newnode2 = List_copy(newnode);
  printf("copy of new node");
  List_print(stdout, newnode2);  
  //List_print(stdout, newnode);
  Node * merged = NULL;
  merged = List_merge(newnode, newnode2);
  List_print(stdout, merged);  
// printf("copy linked list");
    
  /*
  while (newnode!= NULL)
    {
      List_print(stdout, newnode);
      printf("this is the address : %p", newnode->next);  
    }
  */   
//newnode = List_insert_ascend(newnode -> next,3,4);
  //List_print(stdout, newnode);
  //printf("this is the address : %p", newnode->next);

  //List_print(stdout, newnode -> next); 
  return 0;
}

#endif
