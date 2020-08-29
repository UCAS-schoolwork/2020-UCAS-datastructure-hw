#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE 30
#define MAX 300
#define NONE -1
typedef int ElemType;

int s[MAX];
int fst[SPACE];
int lst[SPACE];
int ssp,fsp;
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
    int dat,wid;
    char c;
    scanf("%d",&G->vexnum);
    memset(G,0,sizeof(Graph));
    while(scanf("%d%c",&dat,&c)==2){
        s[ssp++] = dat;
        if(c=='\n')
            break;
    }
    while(scanf("%d%c",&dat,&c)==2){
        fst[fsp++] = dat;
        if(c=='\n')
            break;
    }
    fsp=0;
    while(scanf("%d%c",&dat,&c)==2){
        lst[fsp++] = dat;
    }
    for(int i=1;i<fsp;i++){
        for(int j=fst[i];j<lst[i];j++){
            AddArc(G,i,s[j]);
        }
    }
}
//deep first search
int dfs(Graph *G, int v,int src)
{
    if(v==src&&G->ver[v].info==1)
        return 1;
    G->ver[v].info=1; 
    Arcnode *p = G->ver[v].firstarc;
    for(;p!=0;p=p->nextarc){
        if(dfs(G,p->adjvex,src))
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
    int yes = 0;
    for(int i=1;i<fsp;i++){
       
        for(int j=0;j<fsp;j++)
            G.ver[j].info=0;
        if(dfs(&G,i,i))   
            yes=1;
        
    }
    if(yes)
        printf("yes");
    else 
        printf("no");
    return 0;
}