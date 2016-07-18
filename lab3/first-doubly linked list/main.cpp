#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct DataT
{
    int birth;
    char *name;
};

struct NodeT
{
    void *data;
    NodeT *next;
    NodeT *perv;
};

struct ListT
{
    NodeT *first;
    NodeT *last;
    int length;
};

void insertFirst(ListT &list,void *data)
{
    NodeT *newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->data=data;
    newnode->next=list.first;
    if(list.first==NULL)
        list.last=list.first;
    newnode->perv=NULL;
    list.first=newnode;
    list.length++;
}

void* scandata()
{
    DataT* newdata=(DataT*)malloc(sizeof(DataT));
    int birth;char name[256];
    scanf("%d",&birth);gets(name);
    newdata->birth=birth;
    newdata->name=(char*)malloc(sizeof(char)*strlen(name));
    strcpy(newdata->name,name);
    return newdata;
}

void printdata(void *data)
{
    DataT *newdata=(DataT*)data;
    printf("%d %s ",newdata->birth,newdata->name);
}

void show(ListT &list)
{
    NodeT *pWalker=list.first;
    for (int i=0;i<list.length;i++)
    {
        printdata(pWalker->data);
        pWalker=pWalker->next;
    }
}

int main()
{
    ListT list;
    list.first=list.last=NULL;
    list.length=0;
    insertFirst(list,scandata());
    insertFirst(list,scandata());
    insertFirst(list,scandata());
    insertFirst(list,scandata());
    show(list);
    return 0;
}
