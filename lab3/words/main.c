#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

typedef struct node
{
    struct node *next;
    struct node *perv;
    char *word;
    int nocc;
}NodeT;

typedef struct list
{
    NodeT *first;
    NodeT *last;
    int length;
}ListT;

void insertinorder(ListT *list,char *word)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->word=(char*)malloc(sizeof(char)*(strlen(word)+1));
    strcpy(newnode->word,word);
    if(list->first==NULL)
        {
            newnode->next=NULL;
            newnode->perv=NULL;
            newnode->nocc=1;
            list->first=list->last=newnode;
            list->length=1;
            return;
        }
    if(stricmp(word,list->first->word)<0)
    {
        newnode->next=list->first;
        newnode->perv=NULL;
        newnode->nocc=1;
        list->first->perv=newnode;
        list->first=newnode;
        list->length++;
        return;
    }
    NodeT* pWalker=list->first;
    NodeT* pWaln=pWalker->next;
    while(pWaln!=NULL&&stricmp(pWaln->word,word)<0)
    {
        pWalker=pWalker->next;
        pWaln=pWaln->next;
    }
    if(pWaln==NULL)
    {
        newnode->next=pWaln;
        newnode->perv=pWalker;
        newnode->nocc=1;
        pWalker->next=newnode;
        list->length++;
        list->last=newnode;
        return;
    }
    if(stricmp(pWaln->word,word)==0)
    {
        pWaln->nocc++;
        free(newnode);
        return;
    }
    else
    {
        newnode->next=pWaln;
        newnode->perv=pWalker;
        newnode->nocc=1;
        pWalker->next=newnode;
        pWaln->perv=newnode;
        list->length++;
    }
}

ListT* readl(FILE **fIN,FILE **fOUT,int argc,char *argv[])
{
    if(processArgs(argc,argv,fIN,fOUT))
    {
        ListT* newlist=(ListT*)malloc(sizeof(ListT));
        newlist->first=newlist->last=NULL;
        newlist->length=0;
        char buff[256];
        while(feof(*fIN)==0)
        {
            fscanf(*fIN,"%s",buff);
            insertinorder(newlist,buff);
            //show(newlist,*fOUT);
        }

        return newlist;
    }
}

void show(ListT *list,FILE *fOUT)
{
    NodeT *pWalkbeg=list->first;
    NodeT *pWalkend=list->last;
    while(pWalkbeg!=NULL)//&&pWalkend!=NULL)
    {
        fprintf(fOUT,"%20s:%d %20s:%d\n",
        pWalkbeg->word,pWalkbeg->nocc,
        pWalkend->word,pWalkend->nocc);
        pWalkbeg=pWalkbeg->next;
        pWalkend=pWalkend->perv;
    }
}

int main(int argc,char *argv[])
{
    FILE *fIN=NULL;
    FILE *fOUT=NULL;
    ListT *list=readl(&fIN,&fOUT,argc,argv);
    show(list,fOUT);
    return 0;
}
