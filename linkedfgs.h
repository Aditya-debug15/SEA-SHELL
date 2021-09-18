#ifndef __LINKEDFGS_H
#define __LINKEDFGS_H

typedef struct node node;
typedef struct node* ptrlist;
typedef ptrlist List; 

struct node{
    int pid;
    char* command;
    ptrlist next;
};

ptrlist CreateEmptyList();

ptrlist MakeNode(int x,char* name);

void InsertAtFront(List* L,int x,char* name);

void DeleteNode(ptrlist P);

int presentinlist(List L,int x);

void removefromlist(List* L,int x);

void EmptyList(List* L);

void DeleteList(List* L);

void PrintList(List L);


#endif