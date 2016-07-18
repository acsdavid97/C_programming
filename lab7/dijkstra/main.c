#include <stdio.h>
#include <stdlib.h>
#include "processArgs.h"

#define NMAX 100 /* max no. of nodes */
#define INFTY 32000 /* big value for infinity */
int dist[NMAX]; /* distances */
int cost[NMAX][NMAX];
int parent[NMAX];
int S[NMAX];

int max;
void Dijkstra(int max, int source)
{
    for (int i = 1; i <= max; i++)
        for (int j = 1; j <= max; j++)
            if(cost[i][j]==0)
                cost[i][j]=INFTY;
    for (int i = 1; i <= max; i++,printf("\n"))
        for (int j = 1; j <= max; j++)
            printf("%d ",cost[i][j]);
    int k;
    for (int i = 1; i <= max; i++)
    {
        S[i] = 0; /* set S empty */
        dist[i] = cost[source][i];
        if (dist[i] < INFTY)
            parent[i] = source;
        else
            parent[i] = 0;
    }
    /* add source to set S */
    S[source] = 1;
    parent[source] = 0;
    dist[source] = 0;
    /* build vectors dist and parent */
    int min=INFTY;
    for (int step = 1; step < max; step++)
    {
        for(int i=1; i<=max;i++)
            if(S[i]==0&&dist[i]<min)
            {
                min=dist[i];
                k=i;
            }

        if (min == INFTY) return;
        S[k] = 1; /* add k to set S */
        for (int j = 1; j <= max; j++)
        {
            if (S[j] == 0 && dist[k] + cost[k][j] < dist[j])
            {
                dist[j] = dist[k] + cost[k][j];
                parent[j] = k;
            }
            if (S[j] == 0 && dist[k] + cost[j][k] < dist[j])
            {
                dist[j] = dist[k] + cost[j][k];
                parent[j] = k;
            }
        }

    }
}

int main(int argc,char* argv[])
{
    FILE* fOUT=NULL;
    FILE* fIN=NULL;
    if(processArgs(argc,argv,&fIN,&fOUT))
    {
        int from,to,weight;
        while(feof(fIN)==0)
        {
            fscanf(fIN,"%d%*c",&from);
            fscanf(fIN,"%d%*c",&to);
            fscanf(fIN,"%d%*c",&weight);
            cost[from][to]=weight;
            cost[to][from]=weight;
            if(max<from)
                max=from;
            if(max<to)
                max=to;
        }
        Dijkstra(max,2);
        int s=0;
        for(int i=1;i<=max;i++)
            s+=dist[i];
        fprintf(fOUT,"%d ",s);
        for(int i=1;i<=max;i++)
            fprintf(fOUT,"%d-",parent[i]);
        fprintf(fOUT,"(");
        for(int i=1;i<=max;i++)
            fprintf(fOUT,"%d,",dist[i]);
        fprintf(fOUT,")");

    }
}
