#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE 30
#define NONE -1
#define MAXP 99999
typedef int ElemType;

typedef struct ArcNode{
    int adjvex;
    int weight;
    struct ArcNode * nextarc;
}Arcnode;
typedef struct VNode{
    ElemType data;
    int minpath;
    int mark;
    int info;
    struct ArcNode *firstarc;
}Vnode;
typedef struct GRAPH{
    Vnode ver[SPACE];
    int vexnum;
    int kind;
}Graph;

int AddArc(Graph *G,int v, int w,int weight)
{
    Arcnode *p = G->ver[v].firstarc;
    
    Arcnode *q = (Arcnode *)malloc(sizeof(Arcnode));
    q->adjvex = w;
    q->nextarc = 0;
    q->weight = weight;
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
    int dat,tad,weight;
    char c;
    memset(G,0,sizeof(Graph));
 
    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        scanf("%d",&weight);
        AddArc(G,dat,tad,weight);
    }
}
//deep first search
int dijkstra(Graph *G, int v)
{
    int head,tail;
    head = G->ver[0].info ? 0 : 1;
    tail = head + G->vexnum;
    //init
    for(int i=head;i<tail;i++){
        G->ver[i].minpath = i==v?0:MAXP;
    }
    while(1){
        //find current min vex
        int curminv = -1;
        int curminp = MAXP;
        for(int i=head;i<tail;i++){
            if(G->ver[i].mark == 0 && G->ver[i].minpath < curminp){
                curminp = G->ver[i].minpath;
                curminv = i;
            }
        }
        if(curminv == -1)
            break;
        //update
        Arcnode * p = G->ver[curminv].firstarc;
        int tmp;
        for(;p;p=p->nextarc){
            tmp = G->ver[curminv].minpath+p->weight;
            if(tmp<G->ver[p->adjvex].minpath)
                G->ver[p->adjvex].minpath = tmp;
        }
        G->ver[curminv].mark = 1;
    }

    return 1;
}
int main()
{
    Graph G;
    char c;
    int dat,vexnum;
    scanf("%d",&vexnum);
    scanf("%d",&dat);
    InitGraph(&G);
    G.vexnum = vexnum;
    dijkstra(&G,dat);
    //output
    int head,tail;
    head = G.ver[0].info ? 0 : 1;
    tail = head + G.vexnum;
    for(int i=head;i<tail;i++){
        if(i!=dat)  
            printf("%d%c",G.ver[i].minpath,i==tail-1?'\n':',');
    }

    return 0;
}