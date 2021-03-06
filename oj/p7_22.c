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
    scanf("%d",&G->vexnum);
    memset(G,0,sizeof(Graph));
    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        AddArc(G,dat,tad);
        if((c=getchar())=='\n')
            break;
    }
}
//deep first search
int dfs(Graph *G, int v, int u)
{
    if(u==v)
        return 1;
    if(G->ver[v].info==1)
        return 0;
    G->ver[v].info=1; //avoid circle
    Arcnode *p = G->ver[v].firstarc;
    for(;p!=0;p=p->nextarc){
        if(dfs(G,p->adjvex,u))
            return 1;
    }
    return 0;
}
int main()
{
    Graph G;
    char c;
    int dat,tad;
    InitGraph(&G);
    scanf("%d%c",&dat,&c);
    scanf("%d",&tad);
    if(dfs(&G,dat,tad))
        printf("yes");
    else 
        printf("no");
    return 0;
}