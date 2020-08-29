#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SPACE 30
#define NONE -1
typedef int ElemType;
typedef struct GRAPH{
    ElemType vexs[SPACE];
    ElemType arcs[SPACE][SPACE];
    int vernum;
}Graph;

void InitGraph(Graph * G)
{
    int dat,tad,wid;
    char c;
    scanf("%d",&wid);
    //scanf("%d",&dat);
    memset(G,0,sizeof(Graph));
    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        G->arcs[dat][tad] = 1;
        G->vexs[dat] = G->vexs[tad] = 1;
        if((c=getchar())=='\n')
            break;
    }
}

int InsertVex(Graph *G, int v)
{
    if(G->vexs[v]==1)
        return 0;
    G->vexs[v]=1;
    return 1;
}

int InsertArc(Graph *G, int v, int w)
{
    G->arcs[v][w]=1;
    return 1;
}

int DeleteVex (Graph *G, int v)
{
    if(G->vexs[v]==0)
        return 0;
    G->vexs[v] = 0;
    for(int i=0;i<SPACE;i++)
        G->arcs[v][i] = 0;
    for(int i=0;i<SPACE;i++){
        if(G->vexs[i]){
            G->arcs[i][v] = 0;
        }
    }
    return 1;
}
int DeleteArc(Graph *G, int v, int w)
{
    G->arcs[v][w] = 0;
    return 1;
}
int main()
{
    Graph G;
    char c;
    int dat,tad;
    InitGraph(&G);
    while((c=getchar())!=EOF){
        if(c=='I'){
            if((c=getchar())=='V'){
                //IV
                getchar();
                scanf("%d",&dat);
                InsertVex(&G,dat);
            }
            else if(c=='A'){
                //IA
                getchar();
                scanf("%d%c",&dat,&c);
                scanf("%d",&tad);
                InsertArc(&G,dat,tad);
            }
            getchar();
            getchar();
            continue;
        }
        else if(c=='D'){
            if((c=getchar())=='V'){
                //DV
                getchar();
                scanf("%d",&dat);
                DeleteVex(&G,dat);
            }
            else if(c=='A'){
                //DA
                getchar();
                scanf("%d%c",&dat,&c);
                scanf("%d",&tad);
                DeleteArc(&G, dat,tad);
            }
            getchar();
            getchar();
            continue;
        }
    }
    //output
    for(int i=0;i<SPACE;i++){
        if(G.vexs[i]==1){
            int first=1;
            for(int j=0;j<SPACE;j++){
                if(G.vexs[j]==1){
                    if(!first)
                        printf(",");
                    printf("%d",G.arcs[i][j]);
                    first=0;
                }
            }
            printf("\n");
        }
    }
    return 0;
}