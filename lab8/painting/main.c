#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

typedef struct asdf
{
    int time,cost,speed,index;
    double ratio;
}WorkT;

int compare(void* a,void* b)
{
    WorkT* aa=(WorkT*)a;
    WorkT* bb=(WorkT*)b;
    if(aa->time<bb->time)
        return -1;
    if(aa->time>bb->time)
        return 1;

    if(aa->ratio<bb->ratio)
        return -1;
    if(aa->ratio>bb->ratio)
        return 1;
    return 0;

}

WorkT* readinp(FILE* fIN,int *n,int *d)
{
    fscanf(fIN,"%d %d",n,d);
    int auxt,auxc,auxs;
    WorkT* inp=(WorkT*)malloc(sizeof(WorkT)*(*n));
    for (int i=0;i<*n;i++)
    {
        fscanf(fIN,"%d %d %d",&auxt,&auxc,&auxs);
        inp[i].time=auxt;
        inp[i].cost=auxc;
        inp[i].speed=auxs;
        inp[i].ratio=(double)auxs/auxc;
        inp[i].index=i;
    }
    return inp;
}

int main(int argc,char* argv[])
{
    FILE* fIN=NULL;
    FILE* fOUT=NULL;
    int n,d,t,current=0,cost=0,pervindex=-1;
    WorkT cur;
    cur.ratio=0;
    cur.index=-1;
    cur.cost=0;
    cur.speed=0;
    cur.time=0;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        WorkT* inputs=readinp(fIN,&n,&d);
        qsort(inputs,n,sizeof(WorkT),compare);
        for (int i=0;i<n;i++)
        {
            printf("%d %d %d %d %g\n",inputs[i]);
        }
        for (t=0;current<d;t++)
        {
            for (int i=0;i<n&&inputs[i].time<=t;i++)
            {
                if(inputs[i].time<=t&&cur.ratio<inputs[i].ratio)
                    cur=inputs[i];
                if(inputs[i].time<=t&&cur.ratio==inputs[i].ratio&&cur.speed<inputs[i].speed)
                    cur=inputs[i];
            }

            if(pervindex!=cur.index)
            {
                pervindex=cur.index;
                cost+=cur.cost;
            }
            current+=cur.speed;
        }
    }
    fprintf(fOUT,"%d ",cost);
}
