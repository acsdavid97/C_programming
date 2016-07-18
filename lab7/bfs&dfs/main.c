#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

int m[100][100],reached[100],queue[100],node,max,v[100];

void bfs(int start,FILE* fOUT)
{
    int i,beg=0,last=0;
    reached[start]=1;
    queue[0]=start;
    while(beg<=last)
    {
        node=queue[beg];
        for(i=0;i<max;i++)
            if(m[node][i]==1&&reached[i]==0)//adding all adjacent nodes
            {
                last++;
                queue[last]=i;//enqueue
                reached[i]=1;
            }
             beg++;//dequeue
    }
    fprintf(fOUT,"bfs:\n");
    for(i=0;i<max;i++)
        fprintf(fOUT,"%d ",queue[i]);
    fprintf(fOUT,"\n");
}

void dfs(int start,FILE* fOUT)
{
    int top=0,i;
    v[top]=start;
    for(int i=0;i<max;i++)
        reached[i]=0;
    fprintf(fOUT,"%d ",start);
    while(top>=0)
    {
        node=v[top];
        int first=0;
        for(i=0;i<max&&first==0;i++)
            if(m[node][i]&&reached[i]==0)
            {
                first=1;
                top++;
                fprintf(fOUT,"%d ",i);
                v[top]=i;
                reached[i]=1;
            }
        if(first==0)
            top--;
    }
}

int main(int argc,char* argv[])
{
    FILE *fIN=NULL;
    FILE *fOUT=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        char* buff=malloc(256);char name[10],asdf[10];
        int node,from,to,offset;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        while(sscanf(buff,"%d%n",&node,&offset))
        {
            buff+=offset;
            if(offset<strlen(buff))
                if(max<node)
                    max=node;
        }
        int offset1;
        fgets(buff,256,fIN);
        sscanf(buff,"%s %s",name,asdf);
        buff+=strlen(name)+strlen(asdf)+2;
        while(sscanf(buff,"(%d%n %d%n)",&from,&offset,&to,&offset1))
        {
            buff+=offset+offset1;
            if(offset+offset1<strlen(buff)+1)
                m[from][to]=1;
        }
        bfs(1,fOUT);
        dfs(1,fOUT);
    }
}