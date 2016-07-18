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
    int from,to;
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
    return newdata;
}

Edgedata* createdata2(int from,int to)
{
    Edgedata* newdata=(Edgedata*)malloc(sizeof(Edgedata));
    newdata->from=from;
    newdata->to=to;
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

int find(ListT* list,int num)
{
    NodeT* pWalker=list->first;
    while(pWalker!=NULL)
    {
       if(((Nodedata*)(pWalker->data))->nodenum==num)
            return 1;
        pWalker=pWalker->next;
    }
    return 0;
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

void printlist2(ListT* list)
{
    NodeT* pWalker=list->first;
    while(pWalker!=NULL)
    {
        printf("(%d %d) ",((Edgedata*)(pWalker->data))->from,
               ((Edgedata*)(pWalker->data))->to);
        pWalker=pWalker->next;
    }
    printf("\n");
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
        ListT* liste=(ListT*)malloc(sizeof(ListT));
        listn->first=NULL;
        liste->first=NULL;
        listn->lenght=0;
        liste->lenght=0;
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



        int offset1;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        Edgedata* toins1=(Edgedata*)malloc(sizeof(Edgedata));
        while(sscanf(buff,"(%d%n %d%n)",&from,&offset,&to,&offset1))
        {
            buff+=offset+offset1;
            if(offset+offset1<strlen(buff))
            {
                toins1=createdata2(from,to);
                insert(liste,toins1);
            }
        }
        printlist2(liste);


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

        NodeT* pWalker=liste->first;

        ListT* listnewedge=(ListT*)malloc(sizeof(ListT));
        listnewedge->first=NULL;
        listnewedge->lenght=0;
        int newfrom,newto;
        newfrom=((Edgedata*)(pWalker->data))->from;
        newto=((Edgedata*)(pWalker->data))->to;
        while(pWalker!=NULL)
        {

            newfrom=((Edgedata*)(pWalker->data))->from;
            newto=((Edgedata*)(pWalker->data))->to;
            if(find(listnew,newto)&&find(listnew,newfrom))
            {
                toins1=createdata2(newfrom,newto);
                insert(listnewedge,toins1);
            }
            pWalker=pWalker->next;
        }
        printlist2(listnewedge);

    }
}
