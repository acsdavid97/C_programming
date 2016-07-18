#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

typedef struct node
{
    struct node *left,*right;
    char value;
} NodeT;

void preorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        printf("%c ",p->value);
        preorder( p->left, level + 1 );
        preorder( p->right, level + 1 );
    }
}

void inorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        if(p->left==NULL &&p->right==NULL)
        {
            printf("%c ",p->value);
            return;
        }

        printf("(");
        inorder( p->left, level + 1 );
        printf("%c ",p->value);
        inorder( p->right, level + 1 );
        printf(")");
    }
}

void postorder( NodeT *p, int level )
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1 );
        postorder( p->right, level + 1 );
        printf("%c ",p->value);
    }
}

NodeT *createBIN(char *inputchar, int i)
{

    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    for (;i>=0;i--)
    {
        if(inputchar[i]==' ')
            continue;
        newnode->value=inputchar[i];
        if(isalnum(inputchar[i]))
        {
            newnode->left=newnode->right=NULL;
            return newnode;
        }
        i--;
        newnode->right=createBIN(inputchar,i);
        i--;
        i--;
        newnode->left=createBIN(inputchar,i);
        return newnode;
    }
}

void showtree(NodeT* p,int level)
{
    printf("\npreorder:\n");
    preorder(p,0);
    printf("\ninorder:\n");
    inorder(p,0);
    printf("\npostorder:\n");
    postorder(p,0);
}

void readf(FILE* fIN)
{
    char buff[256];
    NodeT *p;
    while(feof(fIN)==0)
    {
        fgets(buff,sizeof(buff),fIN);
        if(buff[0]=='e')
            p=createBIN(buff+2,strlen(buff)-4);
        if(buff[0]=='p')
            showtree(p,0);

    }
}

int main(int argc,char* argv[])
{
    FILE *fIN=NULL;
    FILE *fOUT=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
        readf(fIN);
    return 0;
}
