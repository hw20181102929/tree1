#include <stdio.h>
#include <stdlib.h>
#define Max 100
#define WQ 65535
struct GNode
{
    int Nv;
    int Ne;
    int G[Max][Max];
};
struct ENode
{
    int v1;
    int v2;
    int weight;
};
struct GNode *begin(int num)
{
    struct GNode * Graph;
    Graph=(struct GNode*)malloc(sizeof(struct GNode));
    Graph->Nv=num;
    Graph->Ne=0;
    int i,j;
    for(i=0;i<Graph->Nv;i++)
    {
        for(j=0;j<Graph->Nv;j++)
        {
            Graph->G[i][j]=WQ;
        }
    }
    return Graph;
}
int findminv(struct GNode *Graph,int dist[])
{
    int i;
    int mindist=WQ;
    int minv;
    for(i=0;i<Graph->Nv;i++)
    {
        if(dist[i]!=0&&dist[i]<mindist)
        {
            mindist=dist[i];
            minv=i;
        }
    }
    if(mindist <WQ )
    {
        return minv;
    }
    else
    {
        return -1;
    }
}
int MinWeight(struct GNode *Graph,int *flag,int *count)
{
    int v;
    int dist[Max];
    int parent[Max];
    int totalweight;
    int Vcount=0;
    int i;
    for(i=0;i<Graph->Nv;i++)
    {
        dist[i]=Graph->G[0][i];
        parent[i]=0;
    }
    dist[0]=0;
    parent[0]=-1;
    Vcount++;
    totalweight=0;
    while(1)
    {
        v=findminv(Graph,dist);
        if(v==-1)
        {
            break;
        }
        totalweight+=dist[v];
        dist[v]=0;
        Vcount++;
        for(int w=0;w<Graph->Nv;w++)
        {
            if(Graph->G[v][w]<WQ&&dist[w]!=0)
            {
                if(Graph->G[v][w]==dist[w]&&dist[w]!=WQ)
                {
                    *flag=1;
                }
                if(Graph->G[v][w]<dist[w])
                {
                    dist[w]=Graph->G[v][w];
                    parent[w]=v;
                }
            }
        }
    }
    for(int k=0;k<Graph->Nv;k++)
    {
        if(dist[k]!=0)
        {
            (*count)++;
            for(int z=0;z<Graph->Nv;z++)
            {
                if(Graph->G[k][z]<WQ)
                {
                    dist[z]=-1;
                }
            }
        }
    }
    if(Vcount==Graph->Nv)
    {
        return totalweight;
    }
    else
    {
        return -1;
    }
}
void Insert(struct GNode *Graph,struct ENode *Edge)
{
    Graph->G[Edge->v1-1][Edge->v2-1]=Edge->weight;
    Graph->G[Edge->v2-1][Edge->v1-1]=Edge->weight;
}
int main()
{
    int b=1;
    int *count;
    count=&b;
    int a=0;
    int *flag;
    flag=&a;
    int Nv,Ne;
    scanf("%d %d",&Nv,&Ne);
    struct GNode * Graph;
    Graph=begin(Nv);
    int i;
    struct ENode *Edge;
    Edge=(struct ENode *)malloc(sizeof(struct ENode));
    for(i=0;i<Ne;i++)
    {
        scanf("%d %d %d",&Edge->v1,&Edge->v2,&Edge->weight);
        Insert(Graph,Edge);
    }
    int totalweight=0;
    totalweight=MinWeight(Graph,flag,count);
    if(totalweight!=-1)
    {
        printf("%d\n",totalweight);
    }
    else
    {
        printf("No MST\n");
        printf("%d\n",*count);
    }
    if(*flag==1&&totalweight!=-1)
    {
        printf("No");
    }
    if(*flag==0&&totalweight!=-1)
        printf("Yes");
    return 0;
}
