#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

typedef struct node
{
    struct node *pNext;
    char *name;
}NodeT;

typedef struct lis
{
    NodeT* first;
    int length;
}ListT;

void insertCirclast(ListT *list,char *name)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->name=(char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(newnode->name,name);
    if(list->first==NULL)
    {
        newnode->pNext=newnode;
        list->first=newnode;
        list->length++;
        return;
    }
    newnode->pNext=list->first;
    NodeT* pWalker=list->first;
    for (int i=0;i<list->length-1;i++)
        pWalker=pWalker->pNext;
    pWalker->pNext=newnode;
    list->length++;
}

void show(ListT* list)
{
    printf("show beg...\n");
    printf("length:%d\n",list->length);
    NodeT *pWalker=list->first;
    if(pWalker==NULL)
    {
        printf("list empty");
        return;
    }
    for (int i=0;i<list->length;i++)
    {
        printf("%s",pWalker->name);
        pWalker=pWalker->pNext;
    }
    printf("...show end\n");
    printf("\n");
}

void deletenext(ListT *list,NodeT *current)
{
    if(list->length<=1)
    {
        list->first=NULL;
        list->length=0;
        return;
    }

    NodeT* aux=current->pNext;
    if(aux==list->first)
        list->first=list->first->pNext;
    current->pNext=aux->pNext;
    list->length--;
    free(aux);
}

void deletenth(ListT *list,int n,FILE *fOUT)
{
    if(list->length==0)
        printf("list empty\n");
    NodeT *pWalker=list->first;
    while(list->length>1)
    {
        for (int i=1;i<n-1;i++)
            pWalker=pWalker->pNext;

        deletenext(list,pWalker);
        pWalker=pWalker->pNext;
    }
    fprintf(fOUT,"%s",pWalker->name);
}

ListT* readc(FILE **fIN,FILE **fOUT,int argc,char *argv[])
{
    ListT* newlist=(ListT*)malloc(sizeof(ListT));
    newlist->first=NULL;
    newlist->length=0;
    if(processArgs(argc,argv,fIN,fOUT))
    {
        int n;char buff[256];
        fscanf(*fIN,"%d%*c",&n);
        for (int i=0;i<n;i++)
        {
            fgets(buff,sizeof(buff),*fIN);
            insertCirclast(newlist,buff);
        }
        return newlist;
    }
    return NULL;
}

int main(int argc,char *argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    ListT* circle=(ListT*)malloc(sizeof(ListT));
    circle=readc(&fIN,&fOUT,argc,argv);
    deletenth(circle,circle->length,fOUT);
    return 0;
}
