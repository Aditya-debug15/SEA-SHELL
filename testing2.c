#include<stdio.h>
#include<stdlib.h>
#include <assert.h>
#include<string.h>
#include "linkedfgs.h"
ptrlist CreateEmptyList()
{
    ptrlist head = NULL;
    return head;
}

ptrlist MakeNode(int x, char *name)
{
    ptrlist P = (ptrlist)malloc(sizeof(node));
    assert(P != NULL);

    P->pid = x;
    P->command = (char*)malloc(1024);
    strcpy(P->command, name);
    P->next = NULL;

    return P;
}

void InsertAtFront(List *L, int x, char *name)
{
    ptrlist P = MakeNode(x, name);
    if (*L == NULL)
    {
        (*L) = P;
    }
    else
    {
        P->next = *L;
        *L = P;
    }
}

void DeleteNode(ptrlist P)
{
    if (P != NULL)
    {
        free(P->command);
        free(P);
    }
}


int presentinlist(List L,int x)
{
    ptrlist temp = L;
    while(temp!= NULL && temp->pid!=x)
    {
        temp=temp->next;
    }
    if(temp==NULL)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void removefromlist(List *L, int x)
{
    ptrlist temp = *L, prev;
    if (temp != NULL && temp->pid == x)
    {
        (*L) = temp->next;
        free(temp);             
        return;
    }
    while (temp != NULL && temp->pid != x)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;

    prev->next = temp->next;
    printf("%s",temp->command);
    free(temp->command);
    free(temp);
}

void EmptyList(List *L)
{
    List Temp = *L;
    ptrlist Curr;
    while (Temp != NULL)
    {
        Curr = Temp;
        Temp = Temp->next;
        DeleteNode(Curr);
    }
    (*L) = NULL;
}

void PrintList(List L)
{
    List walk = L;
    while (walk != NULL)
    {
        printf("%d %s\n", (walk)->pid,walk->command);
        walk = (walk)->next;
    }
}
