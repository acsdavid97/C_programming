#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

//complex data-> number;(duplicate numbers will be put in a list)


typedef struct nod
{
    char *value;
    struct nod *next;
}NodeT;

typedef struct lis
{
    NodeT* first;
    NodeT* last;
}ListT;

ListT* hashtable[100];

int hashf(char* name)
{
    int ha=0;
    for (int i=0;i<2&&i<strlen(name);i++)
        ha=ha*10+(name[i]%10);
    return ha;
}

int find(char* tofind)
{
    int hashvalue=hashf(tofind);
    NodeT* pWalker=hashtable[hashvalue]->first;
    while(pWalker!=NULL)
        if(strcmp(pWalker->value,tofind)==0)
            return 1;
        else
            pWalker=pWalker->next;
    return 0;
}


NodeT* createnode(char* buff)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->value=(char*)malloc(sizeof(char)*sizeof(strlen(buff)));
    strcpy(newnode->value,buff);
    newnode->next=NULL;
    return newnode;
}

void insertnode(char* buff,ListT* list)
{
    NodeT* newnode=createnode(buff);
    if(list->first==NULL)
        list->first=list->last=newnode;
    else
    {
        list->last->next=newnode;
        list->last=list->last->next;
    }
}


void insert(char* toinsert)
{
    char* newname=(char*)malloc(sizeof(char)*sizeof(strlen(toinsert)));
    strcpy(newname,toinsert);
    int hashvalue=hashf(toinsert);
    insertnode(newname,hashtable[hashvalue]);
    printf("succesful insert at hashvalue:%d\n",hashvalue);
}

void printlist(ListT* list)
{
    NodeT* pWalker=list->first;
    while(pWalker!=NULL)
    {
        printf("%s",pWalker->value);
        pWalker=pWalker->next;
    }
}

void list()
{
    for (int i=0;i<100;i++)
        if(hashtable[i]!=NULL)
            printlist(hashtable[i]);
}

void deletenode(char *todelete,ListT* list)
{
    if(todelete==NULL)
    {
        printf("can't delete null node\n");
        return;
    }
    if(list->first==NULL)
    {
        printf("list empty\n");
        return;
    }
    if(strcmp(list->first->value,todelete))
    {
        NodeT* aux=list->first;
        list->first=aux->next;
        if(aux==list->last)
            list->first=list->last=NULL;
        free(aux);
        return;
    }
    NodeT* pWalker=list->first;
    NodeT* pWaln=list->first->next;
    while(pWaln!=NULL&&strcmp(pWaln->value,todelete)!=0)
    {
        pWalker=pWalker->next;
        pWaln=pWaln->next;
    }
    if(pWaln==NULL)
    {
        printf("node not in list\n");
        return;
    }
    pWalker->next=pWaln->next;
    free(pWaln);
    return;
}

void del(char* todelete)
{
    int hashvalue=hashf(todelete);
    deletenode(todelete,hashtable[hashvalue]);
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    for (int i=0;i<100;i++)
    {
        hashtable[i]=(ListT*)malloc(sizeof(ListT));
        hashtable[i]->first=hashtable[i]->last=NULL;
    }

    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        char buff[256];
        while(fgets(buff,sizeof(buff),fIN))
        {
            switch(buff[0])
            {
                case 'i': insert(buff+1); break;
                case 'd': del(buff+1); break;
                case 'f':
                     if(find(buff+1))
                        printf("%s found\n",buff+1);
                     else
                        printf("%s NOT found\n",buff+1);
                    break;
                case 'l': list(); break;
                default: printf("unknown command\n");
            }
        }
    }
    return 0;
}
