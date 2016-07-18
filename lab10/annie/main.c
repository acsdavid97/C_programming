#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"
#define INF=20000000;



int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        int n;
        fscanf(fIN,"%d",&n);
        int* c=(int*)malloc(sizeof(int)*n);
        int* e=(int*)malloc(sizeof(int)*n);
        int** d=(int**)malloc(sizeof(int*)*n);
        for (int i=0;i<n;i++)
            int* d[i]=(int*)malloc(sizeof(int));
        for (int i=0;i<n;i++)
        {
            fscanf(fIN,"%d",e+i);
            fscanf(fIN,"%d",c+i);
        }
    }
    return 0;
}
