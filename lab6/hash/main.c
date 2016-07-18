#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

//complex data-> number;(duplicate numbers will be put in a list)


char* hashtable[512];

int hashf(char* name)
{
    int ha=0;
    for (int i=0;i<2&&i<strlen(name);i++)
        ha=ha*16+(name[i]%16);
    return ha;
}

int secondhash(char *name)
{
    return hashf(name)+256;
}

int find(char* tofind)
{
    int hashvalue=hashf(tofind);
    if(hashtable[hashvalue]!=NULL)
        if(strcmp(tofind,hashtable[hashvalue])==0)
            return hashvalue;
    hashvalue+=256;
    if(hashtable[hashvalue]!=NULL)
        if(strcmp(tofind,hashtable[hashvalue])==0)
            return hashvalue;
    return -1;
}

void insert(char* toinsert)
{
    char* newname=(char*)malloc(sizeof(char)*sizeof(strlen(toinsert)));
    strcpy(newname,toinsert);
    int hashvalue=hashf(toinsert);
    if(hashtable[hashvalue]!=NULL)
        hashvalue=secondhash(toinsert);
    else
    {
        hashtable[hashvalue]=newname;
        printf("insert succesful at hashvalue:%d \n",hashvalue);
        return;
    }
    if(hashtable[hashvalue]!=NULL)
    {
        printf("cannot insert :(\n");
        return;
    }
    hashtable[hashvalue]=newname;
    printf("insert succesful at hashvalue: %d\n",hashvalue);
    return;
}

void list()
{
    for (int i=0;i<512;i++)
        if(hashtable[i]!=NULL)
            printf("%s",hashtable[i]);
}

void del(char* todelete)
{
    int hashval=find(todelete);
    if(hashval>=0)
        hashtable[hashval]=NULL;
    else
        printf("%s not found -> cannot be deleted\n",todelete);
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    for (int i=0;i<512;i++)
        hashtable[i]=NULL;
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
                     if(find(buff+1)>=0)
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
