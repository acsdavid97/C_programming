#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

typedef struct node
{
    struct node *pNext;
    int id;
}NodeT;

typedef struct listt
{
    struct listt *pFirst;
    char name[100];
}SLListT;

SLListT road, garage;
void show(SLListT list,FILE* f)
{
    fprintf(f,"%s ",list.name);
    if(list.pFirst==NULL)
        fprintf(f,"none");
    else
    {
        NodeT *pWalker=list.pFirst;
        while(pWalker!=NULL)
        {
            fprintf(f,"% d",pWalker->id);
            pWalker=pWalker->pNext;
        }
    }
    fprintf(f,"\n");
}
void initList(SLListT *list,char name[])
{
    list->pFirst=NULL;
    strcpy(list->name,name);
}

void insertLast(int id,SLListT* list)
{
    NodeT* newnode =(NodeT*)malloc(sizeof(NodeT));
    newnode->id=id;
    newnode->pNext=NULL;
    if(list->pFirst==NULL)
    {
        list->pFirst=newnode;
        return;
    }
    NodeT* pWalker=list->pFirst;
    while(pWalker->pNext!=NULL)
        pWalker=pWalker->pNext;
    pWalker->pNext=newnode;
}

void insertBeforeFirst(NodeT* pNode,SLListT* list)
{
    pNode->pNext=list->pFirst;
    list->pFirst=pNode;

}

void deleteFirst(SLListT *list)
{
    if(list->pFirst!=NULL)
    {
        NodeT* pNodeToDelete=list->pFirst;
        NodeT* aux=list->pFirst;
        list->pFirst=aux->pNext;
        free(pNodeToDelete);
    }
}

void addTruck(int id,SLListT* list)
{
    NodeT* pNewNode=(NodeT*)malloc(sizeof(NodeT));
    pNewNode->id=id;
    insertBeforeFirst(pNewNode,list);
}

void exitGarage(int id,FILE* f)
{
    NodeT* aux=garage.pFirst;
    if(aux==NULL||aux->id!=id)
        fprintf(f,"error: %d not at exit!\n",id);
    else
    {
        insertLast(id,&road);
        deleteFirst(&garage);
    }
}
int find(int id, SLListT* list)
{
    NodeT* pWalker=list->pFirst;
    while(pWalker!=NULL)
    {
        if(pWalker->id==id)
            return 1;
        pWalker=pWalker->pNext;
    }
    return 0;
}
void deleteNode(int id,SLListT* list)
{
    NodeT* pWalker=list->pFirst;
    NodeT* pPreWalker;
    while(pWalker!=NULL)
    {
        if(pWalker->id==id)
        {
            if(pWalker==list->pFirst)
            {
                deleteFirst(list);
                return;
            }

            else
            {
                pPreWalker->pNext=pWalker->pNext;
                free(pWalker);
                return;
            }
        }
        pPreWalker=pWalker;
        pWalker=pWalker->pNext;

    }
}
void enterGarage(int id,FILE* f)
{
    if(find(id,&road))
    {
        addTruck(id,&garage);
        deleteNode(id,&road);
        return;
    }
    fprintf(f,"%d not found on road\n",id);
}

int main(int argc,char *argv[])//I tried with processArgs but it did not work for me..
{                               //it opened an out put file somewhere and it did not open the input file
    FILE *f=fopen(argv[1],"r");
    FILE *g=fopen(argv[2],"w");
    initList(&garage,"garage");
    initList(&road,"road");
    char buff[40];
    char operation[40];
    int pos=0,num;
    while(fgets(buff,sizeof(buff),f))
    {
        pos=strchr(buff,'(')-buff;
        strcpy(operation,buff);operation[pos]='\0';
        if(strcmp(operation,"On_road")==0)
        {
            sscanf(buff+pos+1,"%d",&num);
            insertLast(num,&road);
            continue;
        }
        if(strcmp(operation,"Enter_garage")==0)
        {
            sscanf(buff+pos+1,"%d",&num);
            enterGarage(num,g);
            continue;
        }
        if(strcmp(operation,"Exit_garage")==0)
        {
            sscanf(buff+pos+1,"%d",&num);
            exitGarage(num,g);
            continue;
        }
        if(strcmp(operation,"Show_trucks")==0)
        {
            char rorg[10];
            sscanf(buff+pos+1,"%s",rorg);
            rorg[strlen(rorg)-1]='\0';
            if(strcmp(rorg,"garage")==0)
                show(garage,g);
            if(strcmp(rorg,"road")==0)
                show(road,g);
            continue;
        }
        fprintf(g,"unknown command\n");
    }
    return 0;
}
