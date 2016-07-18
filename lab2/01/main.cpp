#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct NodeT
{
    int key;
    NodeT *next;
};

struct circularList
{
    int length;
    NodeT * first ;
};

void insertfNode(circularList &list,int data)
{
    NodeT *p=(NodeT*)malloc(sizeof(NodeT));
    p->key=data;
    if(list.first==NULL)
    {
        p->next=p;
        list.first=p;
    }
    else
    {
        NodeT* aux=list.first;
        p->next=aux->next;
        list.first=p;
        aux->next=p;
    }
    list.length++;
}

void deleteKey(circularList &list,int key)
{
    NodeT* current=list.first;
    NodeT* next=list.first->next;
    for (int i;i<list.length;i++)
    {
        if(key==next->key)
        {
            current->next=next->next;
            free(next);
            list.length--;
            return;
        }
        current=current->next;
        next=next->next;
    }
    printf("%d not found in list\n",key);
}

void print(circularList &list)
{
    if(list.first==NULL)
    {
        printf("list empty");
        return;
    }
    NodeT* p=list.first;
    for (int i=0;i<list.length;i++)
    {
        printf("%d ",p->key);
        p=p->next;
    }
    printf("\nlength=%d \n",list.length);
}

NodeT* find(circularList &list,int key)
{
    NodeT* current=list.first;
    for (int i=0;i<list.length;i++)
    {
        if(key==current->key)
            return current;
        current=current->next;
    }
    printf("%d not found in list\n",key);
}

void deleteF(circularList &list)
{
    if(list.first==NULL)
    {
        printf("list empty");
        return;
    }
    NodeT* p=list.first;
    NodeT* aux=list.first;
    for (int i=0;i<list.length-1;i++)
        p=p->next;
    p->next=aux->next;
    list.first=p;
    free(aux);
    list.length--;

}

int main()
{
    circularList pList;
    pList.length=0;
    pList.first=NULL;
    printf("%d test\n",5);
    insertfNode(pList,0);
    insertfNode(pList,2);
    insertfNode(pList,6);
    insertfNode(pList,9);
    print(pList);
    deleteF(pList);
    deleteKey(pList,0);
    print(pList);
    return 0;
}
