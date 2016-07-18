#include <stdio.h>
#include <stdlib.h>

typedef struct asdf
{
    double beg;
    double end;
    double length;
    int index;
}ActivT;

int compare(void* a,void* b)
{
    ActivT* aa=(ActivT*)a;
    ActivT* bb=(ActivT*)b;
    if(aa->length<bb->length)
        return -1;
    if(aa->length>bb->length)
        return 1;
    return 0;

}

int compattible(ActivT* comp,ActivT newact,int compl)
{
    for (int i=0;i<compl;i++)
        if(newact.beg<comp[i].end&&newact.end>comp[i].beg)
            return 0;
    return 1;
}

ActivT* readinp(FILE* fIN,int *n)
{
    fscanf(fIN,"%d",n);
    double auxb,auxe;
    ActivT* inp=(ActivT*)malloc(sizeof(ActivT)*(*n));
    for (int i=0;i<*n;i++)
    {
        fscanf(fIN,"%lf %lf",&auxb,&auxe);
        inp[i].beg=auxb;
        inp[i].end=auxe;
        inp[i].length=auxe-auxb;
        inp[i].index=i;
    }
    return inp;
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    int n;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        ActivT* inputs=readinp(fIN,&n);
        ActivT* comp=(ActivT*)malloc(sizeof(ActivT)*n);
        qsort(inputs,n,sizeof(ActivT),compare);
        int k=0;
        for (int i=0;i<n;i++)
        {
            if(compattible(comp,inputs[i],k))
            {
                comp[k]=inputs[i];
                k++;
            }
        }
        for (int i=0;i<k;i++)
            fprintf(fOUT,"index:%d beg:%g %g\n",comp[i].index,comp[i].beg,comp[i].end);

    }
    return 0;
}
