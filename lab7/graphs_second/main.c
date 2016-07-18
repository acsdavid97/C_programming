#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

typedef struct nod1
{
    void *data;
    struct nod1* next;
}NodeT;

typedef struct lis1
{
    int lenght;
    NodeT* first;
}ListT;

typedef struct
{
    int node;
}Edgedata;

typedef struct
{
    int nodenum;
    ListT* adjacent;
}Nodedata;

Nodedata* createdata1(int num)
{
    Nodedata* newdata=(Nodedata*)malloc(sizeof(Nodedata));
    newdata->nodenum=num;
    newdata->adjacent=(ListT*)malloc(sizeof(ListT));
    newdata->adjacent->first=NULL;
    newdata->adjacent->lenght=0;
    return newdata;
}

Edgedata* createdata2(int num)
{
    Edgedata* newdata=(Edgedata*)malloc(sizeof(Edgedata));
    newdata->node=num;
    return newdata;
}

NodeT* createnode(void* data)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->next=NULL;
    newnode->data=data;
    return newnode;
}

void insert(ListT* list,void* data)
{
    NodeT* newnode=createnode(data);
    NodeT* pWalker=list->first;
    if(pWalker==NULL)
    {
        list->first=newnode;
        list->lenght++;
        return;
    }

    while(pWalker->next!=NULL)
        pWalker=pWalker->next;
    pWalker->next=newnode;
    list->lenght++;
    return;
}

NodeT* find(ListT* list,int num)
{
    NodeT* pWalker=list->first;
    while(pWalker!=NULL)
    {
       if(((Nodedata*)(pWalker->data))->nodenum==num)
            return pWalker;
        pWalker=pWalker->next;
    }
    return NULL;
}

void printlist1(ListT* list)
{
    NodeT* pWalker=list->first;
    while(pWalker!=NULL)
    {
        printf("%d ",((Nodedata*)(pWalker->data))->nodenum);
        pWalker=pWalker->next;
    }
    printf("\n");
}

void printlists(ListT* list)
{
    NodeT* pWalker=list->first;
    NodeT* pWalker2;
    while(pWalker!=NULL)
    {
        pWalker2=((Nodedata*)(pWalker->data))->adjacent->first;
        while(pWalker2!=NULL)
        {
            printf("(%d %d) ",((Nodedata*)(pWalker->data))->nodenum,
                   ((Edgedata*)(pWalker2->data))->node);
            pWalker2=pWalker2->next;
        }
        pWalker=pWalker->next;
        printf("\n");
    }
    printf("\n");
}

void fprintlists(FILE* fOUT,ListT* list)
{
    NodeT* pWalker=list->first;
    NodeT* pWalker2;
    while(pWalker!=NULL)
    {
        pWalker2=((Nodedata*)(pWalker->data))->adjacent->first;
        while(pWalker2!=NULL)
        {
            fprintf(fOUT,"(%d %d) ",((Nodedata*)(pWalker->data))->nodenum,
                   ((Edgedata*)(pWalker2->data))->node);
            pWalker2=pWalker2->next;
        }
        pWalker=pWalker->next;
        fprintf(fOUT,"\n");
    }
    fprintf(fOUT,"\n");
}

int main(int argc,char* argv[])
{
    FILE *fIN=NULL;
    FILE *fOUT=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        char* buff=malloc(256);char name[10],asdf[10];
        int node,from,to,offset;
        ListT* listn=(ListT*)malloc(sizeof(ListT));
        listn->first=NULL;
        listn->lenght=0;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        Nodedata* toins=(Nodedata*)malloc(sizeof(Nodedata));
        while(sscanf(buff,"%d%n",&node,&offset))
        {
            buff+=offset;
            if(offset<strlen(buff))
            {
                toins=createdata1(node);
                insert(listn,toins);
            }
        }
        printlist1(listn);

        NodeT* pWalker;
        int offset1;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        Edgedata* toins1=(Edgedata*)malloc(sizeof(Edgedata));
        while(sscanf(buff,"(%d%n %d%n)",&from,&offset,&to,&offset1))
        {
            buff+=offset+offset1;
            if(offset+offset1<strlen(buff)+1)
            {
                pWalker=listn->first;
                while(pWalker!=NULL)
                {
                    if(((Nodedata*)(pWalker->data))->nodenum==from)
                    {
                        toins1=createdata2(to);
                        insert(((Nodedata*)(pWalker->data))->adjacent,toins1);
                        break;
                    }
                    pWalker=pWalker->next;
                }
            }
        }
        printlists(listn);

        ListT* listnew=(ListT*)malloc(sizeof(ListT));
        listnew->first=NULL;
        listnew->lenght=0;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        while(sscanf(buff,"%d%n",&node,&offset))
        {
            buff+=offset;
            if(offset<strlen(buff))
            {
                toins=createdata1(node);
                insert(listnew,toins);
            }
        }
        printlist1(listnew);

        pWalker=listn->first;
        int newfrom,newto;
        NodeT* pWalker2;
        while(pWalker!=NULL)
        {
            newfrom=((Nodedata*)(pWalker->data))->nodenum;

            pWalker2=((Nodedata*)(pWalker->data))->adjacent->first;
            while(pWalker2!=NULL)
            {
                newto=((Edgedata*)(pWalker2->data))->node;
                if(find(listnew,newto)!=NULL&&find(listnew,newfrom)!=NULL)
                {
                    toins1=createdata2(newto);
                    insert(((Nodedata*)(find(listnew,newfrom)->data))->adjacent,toins1);
                }
                pWalker2=pWalker2->next;
            }
            pWalker=pWalker->next;
        }
        fprintlists(fOUT,listnew);
    }
}
