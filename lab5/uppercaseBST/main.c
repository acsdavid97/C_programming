#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

typedef struct nod
{
    char value;
    struct nod *left;
    struct nod *right;
}NodeT;

NodeT* createNode(char values)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->left=newnode->right=NULL;
    newnode->value=values;
    return newnode;
}

void preorder( NodeT *p, int level ,FILE* fOUT)
{
    if ( p != NULL )
    {
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        fprintf(fOUT,"%2.2c\n",p->value);
        preorder( p->left, level + 1 ,fOUT);
        preorder( p->right, level + 1 ,fOUT);
    }
}

void inorder( NodeT *p, int level ,FILE* fOUT)
{
    if ( p != NULL )
    {
        inorder( p->left, level + 1 ,fOUT);
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        fprintf(fOUT,"%2.2c\n",p->value);
        inorder( p->right, level + 1 ,fOUT);
    }
}

void postorder( NodeT *p, int level ,FILE* fOUT)
{
    if ( p != NULL )
    {
        postorder( p->left, level + 1 ,fOUT);
        postorder( p->right, level + 1 ,fOUT);
        for ( int i = 0; i <= level; i++ ) printf( " " ); /* for nice listing */
        fprintf(fOUT,"%2.2c\n",p->value);
    }
}

void traversal(char buff1,NodeT* root,FILE* fOUT)
{
    switch(buff1)
    {
        case 'p': fprintf(fOUT,"preorder:\n"); preorder(root,0,fOUT); break;
        case 'P': fprintf(fOUT,"postorder:\n"); postorder(root,0,fOUT); break;
        case 'i': fprintf(fOUT,"inorder:\n"); inorder(root,0,fOUT); break;
        default : printf("Unkwown command\n");
    }
}

NodeT* find(char name,NodeT* root)
{
    if(root==NULL)
        return NULL;
    if(name<root->value)
        return find(name,root->left);
    if(name>root->value)
        return find(name,root->right);
    return root;
}

NodeT* insert(NodeT* toinsert,NodeT* node)
{
    if(node==NULL)
        return toinsert;
    if(toinsert->value<node->value)
        node->right=insert(toinsert,node->right);
    else
        if(toinsert->value>node->value)
            node->left=insert(toinsert,node->left);
        else
            printf("Node exists\n");
    return node;
}


void printtree(NodeT* root,FILE* fOUT)
{
    if(root==NULL)
        return;
    printf("%c ",root->value);
    printtree(root->left,fOUT);
    printtree(root->right,fOUT);
}

NodeT* deletenode(NodeT* parent,NodeT* curr,NodeT* root,char buff,int dir)//dir=1 right //dir=0 root //dir=-1 left
{
    if(curr==NULL)
    {
        printf("node to delete not found");
        return root;
    }

    if(buff<curr->value)
        return deletenode(curr,curr->left,root,buff,-1);
    if(buff>curr->value)
        return deletenode(curr,curr->right,root,buff,1);
    if(curr==root&&root->left==NULL&&root->right==NULL)
        return NULL;
    if(curr->left==NULL&&curr->right==NULL)
    {
        if(dir==-1)
            parent->left=NULL;
        if(dir==1)
            parent->right=NULL;
        return root;
    }
    if(curr->left==NULL)
    {
        if(dir==1)
            parent->right=curr->right;
        if(dir==-1)
            parent->left=curr->right;
        return root;
    }
    if(curr->right==NULL)
    {
        if(dir==1)
            parent->right=curr->left;
        if(dir==-1)
            parent->left=curr->left;
        free(curr);
        return root;
    }
    NodeT* pWalker=curr;
    if(dir==1)
    {
        while(pWalker->left!=NULL)
            pWalker=pWalker->left;
        if(curr!=root)
            parent->right=pWalker;
    }

    else
    {
        while(pWalker->right!=NULL)
            pWalker=pWalker->right;
        parent->left=pWalker;
    }
    return root;


}

int main(int argc,char *argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    NodeT *root=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        char buff[256];
        while(fgets(buff,sizeof(buff),fIN))
        {
            NodeT* auxn;
            switch (buff[0])
            {
                case 'i': auxn=createNode(buff[1]); root=insert(auxn,root); break;
                case 'd': root=deletenode(NULL,root,root,buff[1],0); break;
                case 't': traversal(buff[1],root,fOUT);
                    break;
                case 'f': auxn=find(buff[1],root);
                    if(auxn!=NULL)
                        printf("found\n");
                    else
                        printf("not found\n");
                    break;
                default: printf("Unknown command\n");
            }
        }
    }
    fclose(fIN);
    fclose(fOUT);
    return 0;
}
