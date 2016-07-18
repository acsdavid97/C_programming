#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processArgs.h"

int d[2000][2000];

int minimum(int a,int b,int c)
{
    if(a>b)
        a=b;
    if(a>c)
        a=c;
    return a;
}

int levf(char* a,char* b,int n,int m)
{
    for (int i=0;i<=n;i++)
        d[i][0]=i;
    for (int j=0;j<=m;j++)
        d[0][j]=j;
    int cost;
    for (int i=1;i<=n;i++)
    {
        for (int j=1;j<=m;j++)
        {
            if(a[i-1]==b[j-1])
                cost=0;
            else
                cost=1;
            d[i][j]=minimum(d[i-1][j]+1,d[i][j-1]+1,d[i-1][j-1]+cost);
        }
    }

    return d[n][m];
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        char* a=(char*)malloc(sizeof(char)*2000);
        char* b=(char*)malloc(sizeof(char)*2000);
        int n;
        fscanf(fIN,"%d%*c",&n);
        for (int i=0;i<n;i++)
        {
            fgets(a,2000,fIN);
            fgets(b,2000,fIN);
            int lev=levf(a,b,strlen(a),strlen(b));
            fprintf(fOUT,"%d\n",lev);
        }

    }
    return 0;
}
