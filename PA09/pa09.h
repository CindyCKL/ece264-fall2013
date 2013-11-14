#ifndef PA09_H
#define PA09_H

typedef struct _huffnode {
  int value; //is this supposed to be the data?
    struct _huffnode * left;
    struct _huffnode * right;
} HuffNode;

typedef struct _stack {
    struct _stack * next;
    HuffNode * node;
} Stack;



void Huff_postOrderPrint(HuffNode *tree, FILE * fptr);
HuffNode * HuffNode_create(int data);
Stack * Stack_push(Stack * stackcall, HuffNode *treenode);
Stack * Stack_pop(Stack * stackcall);
HuffNode * makingatreewithbyte(FILE * fptr);
void destroy(HuffNode * head);
/*
HuffNode * makingatreewithbits(FILE *fptr);
unsigned char getcommand(FILE * fptr, int * cmdloc, unsigned char * ourbyte);
int getdata(FILE * fptr, int * cmdloc, unsigned char * ourbyte);
*/


#endif
