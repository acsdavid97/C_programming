#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>// we need it for intrptr_t

typedef struct node
{
    int value;
    struct node *pNext;
}NodeT;

typedef struct lis
{
    NodeT *first;
    NodeT *last;
}ListT;

NodeT *xor(NodeT *a,NodeT *b)
{
    return (NodeT*)((intptr_t)a^(intptr_t)b);//intptr_t  to convert pointer to int for xor to work
}

NodeT* insertinlist(NodeT *prev,NodeT *curr,int value)
{
    NodeT* next=(NodeT*)malloc(sizeof(NodeT));
    next->value=value;
    next->pNext=curr;

    if(prev==NULL&&curr==NULL)
        return next;//list empty, initializing
    if(prev==NULL)
    {
        curr->pNext=next;
        next->pNext=curr;
        return next;
    }
    curr->pNext=xor(prev,next);//we can change the current next
    return next;
}

ListT* readl(FILE *f)
{
    int aux=0;
    ListT* list=(ListT*)malloc(sizeof(ListT));
    list->first=list->last=NULL;
    fscanf(f,"%d",&aux);
    list->last=list->first=insertinlist(NULL,NULL,aux);
    while(feof(f)==0)
    {
        fscanf(f,"%d",&aux);
        list->last=insertinlist(list->last->pNext,list->last,aux);
    }
    return list;
}

void show(NodeT* nod)
{
    NodeT *prev,*pWalker;
    prev=pWalker=nod;
    while(pWalker!=NULL)
    {
        printf("%d ",pWalker->value);
        if(pWalker->pNext==pWalker)
            break;
        if(pWalker==prev)
            pWalker=pWalker->pNext;
        else
        {
            NodeT *aux=pWalker;
            pWalker=xor(prev,pWalker->pNext);
            prev=aux;
        }
    }
}

int main(int argc,char *argv[])
{
    FILE *f=NULL,*g=NULL;
    if(processArgs(argc,argv,&f,&g))
    {
        ListT* list=readl(f);
        show(list->first);
    }
    return 0;
}

