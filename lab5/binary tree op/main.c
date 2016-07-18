#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct med
{
    char name[30];
    double price;
    int amount;
    int dateOfManufacturing;
    int dateOfExpiration;
}MedT;

typedef struct nod
{
    MedT* value;
    struct nod *left;
    struct nod *right;
}NodeT;

NodeT* createNode(MedT* values)
{
    NodeT* newnode=(NodeT*)malloc(sizeof(NodeT));
    newnode->left=newnode->right=NULL;
    newnode->value=values;
    return newnode;
}



NodeT* find(char name[],NodeT* root)
{
    if(root==NULL)
        return NULL;
    if(stricmp(name,root->value->name)<0)
        return find(name,root->left);
    if(stricmp(name,root->value->name)>0)
        return find(name,root->right);
    return root;
}

void update(char* buff,NodeT* root)
{
    char* str=strtok(buff,",\n");
    NodeT* foundN=find(str,root);
    if(foundN==NULL)
    {
        printf("can't find node to update\n");
        return;
    }
    str=strtok(NULL,",\n");
    if(stricmp(str,"~")!=0)
        strcpy(foundN->value->name,str);
    str=strtok(NULL,",\n");
    if(stricmp(str,"~")!=0)
        sscanf(str,"%lf",&foundN->value->price);
    str=strtok(NULL,",\n");
    if(stricmp(str,"~")!=0)
        sscanf(str,"%d",&foundN->value->amount);
    str=strtok(NULL,",\n");
    if(stricmp(str,"~")!=0)
        sscanf(str,"%d",&foundN->value->dateOfManufacturing);
    str=strtok(NULL,",\n");
    if(stricmp(str,"~")!=0)
        sscanf(str,"%d",&foundN->value->dateOfExpiration);

}

MedT* readvalues(char* buff)
{
    MedT* newvalues=(MedT*)malloc(sizeof(MedT));
    char* str=strtok(buff,",\n");
    strcpy(newvalues->name,str);
    str=strtok(NULL,",\n");
    sscanf(str,"%lf",&newvalues->price);
    str=strtok(NULL,",\n");
    sscanf(str,"%d",&newvalues->amount);
    str=strtok(NULL,",\n");
    sscanf(str,"%d",&newvalues->dateOfManufacturing);
    str=strtok(NULL,",\n");
    sscanf(str,"%d",&newvalues->dateOfExpiration);
    return newvalues;
}

NodeT* insert(NodeT* toinsert,NodeT* node)
{
    if(node==NULL)
        return toinsert;
    if(stricmp(node->value->name,toinsert->value->name)<0)
        node->right=insert(toinsert,node->right);
    else
        if(stricmp(node->value->name,toinsert->value->name)>0)
            node->left=insert(toinsert,node->left);
        else
            printf("Node exists\n");
    return node;
}

void printvalue(MedT* value,FILE *fOUT)
{
    fprintf(fOUT,"%s,%g,%i,%i,%i\n",value->name,value->price,
            value->amount,value->dateOfManufacturing,value->dateOfExpiration);
}

void printtree(NodeT* root,FILE* fOUT)
{
    if(root==NULL)
        return;
    printvalue(root->value,fOUT);
    printtree(root->left,fOUT);
    printtree(root->right,fOUT);
}

NodeT* deletenode(NodeT* parent,NodeT* curr,NodeT* root,char *buff,int dir)//dir=1 right //dir=0 root //dir=-1 left
{
    if(curr==NULL)
    {
        printf("node to delete not found");
        return root;
    }

    if(stricmp(buff,curr->value->name)<0)
        return deletenode(curr,curr->left,root,buff,-1);
    if(stricmp(buff,curr->value->name)>0)
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

void createexp(NodeT* root,NodeT** roote,int currentdate)
{
    if(root==NULL) return;
    NodeT* aux=createNode(root->value);
    if(currentdate>aux->value->dateOfExpiration)
        *roote=insert(aux,*roote);
    createexp(root->left,roote,currentdate);
    createexp(root->right,roote,currentdate);

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
            MedT* auxm;NodeT* auxn;
            switch (buff[0])
            {
                case 'i': auxm=readvalues(buff+1); auxn=createNode(auxm); root=insert(auxn,root); break;
                case 'u': update(buff+1,root); break;
                case 'p': printtree(root,fOUT); fprintf(fOUT,"\n"); break;
                case 'd': buff[strlen(buff)-1]='\0'; root=deletenode(NULL,root,root,buff+1,0); break;
                default: printf("Unknown command\n");
            }
        }
    }
    NodeT *roote=NULL;
    int currentdate;printf("current date:");
    scanf("%d",&currentdate);
    createexp(root,&roote,currentdate);
    fprintf(fOUT,"\nexpired products:\n");
    printtree(roote,fOUT);
    fclose(fIN);
    fclose(fOUT);
    return 0;
}
