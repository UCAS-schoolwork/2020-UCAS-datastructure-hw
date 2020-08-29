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
    int MPL;
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
    //mark existing vex
    G->ver[v].info = G->ver[w].info = 1;
    return 1;
}
void InitGraph(Graph * G)
{
    int dat,tad,wid;
    char c;
    memset(G,0,sizeof(Graph));
    scanf("%d",&G->vexnum);
    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        AddArc(G,dat,tad);
        if((c=getchar())=='\n')
            break;
    }
}
//deep first search
int dfs(Graph *G, int v,int k)
{
    int maxk = k;
    int tmp;
    Arcnode *p = G->ver[v].firstarc;
    for(;p!=0;p=p->nextarc){
        tmp = dfs(G,p->adjvex,k+1);
        if(tmp>maxk)
            maxk=tmp;
    }
    return maxk;
}
int main()
{
    Graph G;
    char c;
    
    InitGraph(&G);
    int cnt=0;
    for(int i=0;i<SPACE;i++){
        if(G.ver[i].info == 1){
            G.ver[i].MPL = dfs(&G,i,0);
            cnt++;
            printf("%d%c",G.ver[i].MPL,cnt==G.vexnum?'\n':',');
        }
    }
    
    return 0;
}