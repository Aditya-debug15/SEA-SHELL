#include "headers.h"
#include "linkedfgs.h"
#include <assert.h>
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
ptrlist MakeNodeso(int x, char *name,int job_num)
{
    ptrlist P = (ptrlist)malloc(sizeof(node));
    assert(P != NULL);
    P->job_num=job_num;
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
void Insertso(List* L,int pid,int job_num,char* name)
{
    ptrlist P = MakeNodeso(pid,name,job_num);
    if (*L == NULL)
    {
        (*L) = P;
    }
    else if(strcmp((*L)->command,name)>0)
    {
        P->next=(*L);
        (*L)=P;
    } 
    else
    {
        ptrlist temp = *L;
        while(temp->next!=NULL && strcmp(temp->next->command,name)<=0)
        {
            temp=temp->next;
        }
        P->next=temp->next;
        temp->next=P;
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

int pidfromjob(List L,int job_num)
{
    ptrlist temp = L;
    while (temp!=NULL && temp->job_num!=job_num)
    {
        temp=temp->next;
    }
    if(temp==NULL)
    {
        return -1;
    }
    else{
        return temp->pid;
    }
}

void removefromlist(List *L, int x)
{
    ptrlist temp = *L, prev;
    if (temp != NULL && temp->pid == x)
    {
        (*L) = temp->next;
        printf("%s",temp->command);
        free(temp->command);
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
        printf("[%d] %s [%d]\n", (walk)->job_num,walk->command,walk->pid);
        walk = (walk)->next;
    }
}