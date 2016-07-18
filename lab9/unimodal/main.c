#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

double* readinp(FILE* fIN,int *n)
{
    fscanf(fIN,"%d",n);
    double *array=(double*)malloc(sizeof(double)*(*n));
    for (int i=0;i<*n;i++)
        fscanf(fIN,"%lf",array+i);
    return array;
}

double divide(double* array,int beg,int end)
{
    if(beg==end)
        return array[beg];
    int m=(beg+end)/2;
    if(array[beg]<=array[beg+1]&&array[m]<=array[m-1])
        return divide(array,beg,m);
    if(array[m+1]<=array[m+2]&&array[end]<=array[end-1])
        return divide(array,m+1,end);
    if(array[m]>array[end]&&array[m]>array[beg])
        return array[m];
    if(array[end]>array[beg])
        return array[end];
    return array[beg];
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    int n;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        double* array=readinp(fIN,&n);
        int beg=0;int end=n-1;
        double fin=divide(array,beg,end);
        fprintf(fOUT,"%g",fin);
    }
    return 0;
}
