#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

typedef struct
{
    int beg,end;
}SubT;

int calcsum(int *array,SubT sub)
{   int s=0;
    for (int i=sub.beg;i<=sub.end;i++)
        s+=array[i];
    return s;
}

int* readinp(FILE* fIN,int *n)
{
    fscanf(fIN,"%d",n);
    int *array=(int*)malloc(sizeof(int)*(*n));
    for (int i=0;i<*n;i++)
        fscanf(fIN,"%d",array+i);
    return array;
}

SubT merge(int* array,SubT first,SubT second)
{
    int f=calcsum(array,first);
    int s=calcsum(array,second);
    int max;
    SubT maxs;
    if(f>s)
    {
        max=f;
        maxs=first;
    }
    else
    {
        max=s;
        maxs=second;
    }
    SubT merged;
    merged.beg=first.beg;
    merged.end=second.end;
    int mer=calcsum(array,merged);
    if(mer>max)
        return merged;
    return maxs;
}

SubT divide(int* array,SubT curr)
{
    if(curr.beg==curr.end)
        return curr;
    SubT firstsub,secondsub;
    int m=(curr.beg+curr.end)/2;
    firstsub.beg=curr.beg;
    firstsub.end=m;
    secondsub.beg=m+1;
    secondsub.end=curr.end;
    SubT first=divide(array,firstsub);
    SubT second=divide(array,secondsub);
    SubT merged=merge(array,first,second);
    return merged;
}

int main(int argc,char *argv[])
{
    int n;
    FILE *fIN=NULL;
    FILE *fOUT=NULL;

    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        int *array=readinp(fIN,&n);
        SubT curr;curr.beg=0;curr.end=n-1;
        SubT fin=divide(array,curr);
        fprintf(fOUT,"%d",calcsum(array,fin));
    }
    return 0;
}
