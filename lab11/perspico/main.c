#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

int per[4][4];

void swap(int **m,int i1,int j1,int i2,int j2)
{
    int aux=m[i1][j1];
    m[i1][j1]=m[i2][[j2];
    m[i2][j2]=aux;
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;

    if(processArgs(argc,argv,&fIN,&fOUT))
    {

    }
    return 0;
}
