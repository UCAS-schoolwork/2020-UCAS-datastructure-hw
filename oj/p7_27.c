#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE 30
#define NONE -1
typedef int ElemType;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode * nextarc;
}Arcnode;
typedef struct VNode{
    ElemType data;
    int info;
    struct ArcNode *firstarc;
}Vnode;
typedef struct GRAPH{
    Vnode ver[SPACE];
    int vexnum;
    int kind;
}Graph;

int AddArc(Graph *G,int v, int w)
{
    Arcnode *p = G->ver[v].firstarc;
    
    Arcnode *q = (Arcnode *)malloc(sizeof(Arcnode));
    q->adjvex = w;
    q->nextarc = 0;
    if(!p)
        G->ver[v].firstarc=q;
    else {
        for(;p->nextarc!=0;p=p->nextarc)
            ;
        p->nextarc = q;
    }
    return 1;
}
void InitGraph(Graph * G)
{
    int dat,tad,wid;
    char c;
   
    memset(G,0,sizeof(Graph));
    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        AddArc(G,dat,tad);
        if((c=getchar())=='\n')
            break;
    }
}
//deep first search
int dfs(Graph *G, int v, int u,int k,int tark)
{
    if(u==v)
        if(k==tark)
            return 1;
        else 
            return 0;
    if(G->ver[v].info==1)
        return 0;
    G->ver[v].info=1; //avoid circle
    Arcnode *p = G->ver[v].firstarc;
    for(;p!=0;p=p->nextarc){
        if(dfs(G,p->adjvex,u,k+1,tark))
            return 1;
    }
    G->ver[v].info=0;
    return 0;
}
int main()
{
    Graph G;
    char c;
    int dat,tad,v,u;
    scanf("%d%c%d",&dat,&c,&tad);
    scanf("%d%c%d",&v,&c,&u);
    InitGraph(&G);
    if(dfs(&G,v,u,0,tad))
        printf("yes");
    else 
        printf("no");
    return 0;
}