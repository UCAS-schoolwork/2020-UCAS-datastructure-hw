#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SPACE 30
#define NONE -1
typedef char ElemType;

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
    //mark existing vex
    G->ver[v].info = G->ver[w].info = 1;
    return 1;
}
void InitGraph(Graph * G)
{
    int dat,tad;
    char c;
    memset(G,0,sizeof(Graph));
    scanf("%d",&G->vexnum);
    int veri=0;
    while((c=getchar())!=EOF)
    {
        if(isalpha(c)){
            G->ver[veri].data = c;
            veri++;
        }
        else if(c=='+'||c=='-'||c=='*'||c=='/'){
            G->ver[veri].data = c;
            scanf("%d%d",&dat,&tad);
            AddArc(G,veri,tad);
            AddArc(G,veri,dat);
            veri++;
        }
    }
}
//search in last order
void lastorder(Graph *G, int v)
{
    Arcnode *p = G->ver[v].firstarc;
    for(;p!=0;p=p->nextarc){
        lastorder(G,p->adjvex);
    }
    printf("%c",G->ver[v].data);
}
int main()
{
    Graph G;
    char c;
    
    InitGraph(&G);
    lastorder(&G,0);
    
    return 0;
}