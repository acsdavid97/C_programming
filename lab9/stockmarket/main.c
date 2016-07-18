#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

typedef struct
{
    int beg,end;
}BesT;

double* readinp(FILE* fIN,int *n)
{
    fscanf(fIN,"%d",n);
    double *array=(double*)malloc(sizeof(double)*(*n));
    for (int i=0;i<*n;i++)
        fscanf(fIN,"%lf",array+i);
    return array;
}

BesT merge(double* array,BesT f,BesT s)
{
    double prof=array[f.end]-array[f.beg];
    BesT pro=f;
    if(array[s.end]-array[s.beg]>prof)
    {
        pro=s;
        prof=array[s.end]-array[s.beg];
    }
    if(array[s.end]-array[f.beg]>prof)
    {
        pro.beg=f.beg;
        pro.end=s.end;
        prof=array[s.end]-array[f.beg];
    }
    return pro;

}

BesT divide(double* array,BesT curr)
{
    if(curr.beg==curr.end)
        return curr;
    int m=(curr.beg+curr.end)/2;
    BesT first;first.beg=curr.beg;first.end=m;
    BesT second;second.beg=m+1;second.end=curr.end;
    BesT f=divide(array,first);
    BesT s=divide(array,second);
    BesT merged=merge(array,f,s);
    return merged;
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    int n;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        double* array=readinp(fIN,&n);
        BesT curr;curr.beg=0;curr.end=n-1;
        BesT fin=divide(array,curr);
        fprintf(fOUT,"%g",array[fin.end]-array[fin.beg]);
    }
    return 0;
}
