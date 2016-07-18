#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

struct NodeT
{
    NodeT *next;
    char* str;
};

struct ListT
{
    int length;
    NodeT *first;
};

NodeT* findnthNode(ListT &list,int n)
{
    n=n%list.length;
    NodeT *pWalker=list.first;
    for (int i=0;i<n;i++)
        pWalker=pWalker->next;
    return pWalker;
}


NodeT* findpervNode(ListT &list,char* str)
{
    NodeT *pWalker=list.first;
    for (int i=0;i<list.length&&strcmp(pWalker->next->str,str)!=0;i++)
        pWalker=pWalker->next;
    if(strcmp(pWalker->next->str,str)==0)
        return pWalker;
    return NULL;
}

void insertfirst(ListT &list,char *str)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->str=(char*)malloc(sizeof(char)*(strlen(str)+1));
    strcpy(newnode->str,str);
    if (list.first==NULL)
    {
        newnode->next=newnode;
        list.first=newnode;
        return;
    }
    newnode->next=list.first;
    NodeT* pWalker=findpervNode(list,list.first->str);
    pWalker->next=newnode;
    list.first=newnode;
    list.length++;
}

void deleteNode (ListT &list, NodeT *node)
{
    NodeT *perv=findpervNode(list,node->str);
    perv->next=node->next;
    free(node);
    list.length--;
}

void printlist(ListT &list)
{
    NodeT *pWalker=(NodeT*)malloc(sizeof(NodeT));
    pWalker=list.first;
    if(list.first==NULL)
    {
        printf("list is empty\n");
        return;
    }
    for (int i=0;i<list.length;i++)
    {
        printf("%s\n",pWalker->str);
        pWalker=pWalker->next;
    }
    printf("\n");
}

int read_inputs(ListT &list)
{
    int i=1;char *aux;
    strcpy(aux,"aux");
    while(atoi(aux)==0)
    {
        gets(aux);
        insertfirst(list,aux);
        i++;
    }
    printlist(list);
    return atoi(aux);
}

void put_in_second(ListT &list1,ListT &list2,int n)
{
    while(list1.length>1)
    {
        insertfirst(list2,findnthNode(list1,n)->next->str);
        deleteNode(list1,findnthNode(list1,n));
    }
}
int main()
{
    ListT list1,list2;
    list1.length=list2.length=0;
    list1.first=list2.first=NULL;
    put_in_second(list1,list2,read_inputs(list1));
    printlist(list1);
    printlist(list2);
    return 0;
}
