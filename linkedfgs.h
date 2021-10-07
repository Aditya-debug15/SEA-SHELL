#ifndef __LINKEDFGS_H
#define __LINKEDFGS_H

typedef struct node node;
typedef struct node* ptrlist;
typedef ptrlist List; 

struct node{
    char* command;
    int pid;
    int job_num;
    ptrlist next;
};

ptrlist     CreateEmptyList();

ptrlist     MakeNode(int x,char* name);
ptrlist     MakeNodeso(int x,char* name,int job_num);

void        InsertAtFront(List* L,int x,char* name);

void        Insertso(List* L,int pid,int job_num,char* name);

void        DeleteNode(ptrlist P);

int         presentinlist(List L,int x);

int         pidfromjob(List L,int job_num);

void        commfrompid(List L,int pid,char M[]);

void        removefromlist(List* L,int x);

void        removefromlist_withoutprinting(List *L, int x);

void        EmptyList(List* L);

void        DeleteList(List* L);

void        PrintList(List L);


#endif