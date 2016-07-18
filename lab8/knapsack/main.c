#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

typedef struct asdf
{
    double weight;
    double value;
    double ratio;
}ItemT;

int compare(void* a,void* b)
{
    ItemT* aa=(ItemT*)a;
    ItemT* bb=(ItemT*)b;
    if(aa->ratio>bb->ratio)
        return -1;
    if(aa->ratio<bb->ratio)
        return 1;
    return 0;
}

ItemT* readinp(FILE* fIN,double *maxw,int *n)
{
    fscanf(fIN,"%lf %d",maxw,n);
    double auxw,auxv;
    ItemT* inp=(ItemT*)malloc(sizeof(ItemT)*(*n));
    for (int i=0;i<*n;i++)
    {
        fscanf(fIN,"%lf %lf",&auxw,&auxv);
        inp[i].weight=auxw;
        inp[i].value=auxv;
        inp[i].ratio=auxv/auxw;
    }
    return inp;
}

int main(int argc,char* argv[])
{
    FILE *fIN=NULL;
    FILE *fOUT=NULL;
    double maxw,tvalue=0,s,part;
    int n;
    ItemT* inp;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        inp=readinp(fIN,&maxw,&n);
        qsort(inp,n,sizeof(ItemT),compare);
        for (int i=0;i<n;i++)
            if(s+inp[i].weight<maxw)
            {
                s+=inp[i].weight;
                tvalue+=inp[i].value;
            }
        fprintf(fOUT,"%g %g\n",s,tvalue);
        s=tvalue=0;
        for (int i=0;i<n;i++)
            if(s<maxw)
            {
                if(maxw-s>inp[i].weight)
                    part=1;
                else
                    part=(maxw-s)/inp[i].weight;
                s+=inp[i].weight*part;
                tvalue+=inp[i].value*part;
            }
        fprintf(fOUT,"%g %g\n",s,tvalue);
    }

    return 0;
}
