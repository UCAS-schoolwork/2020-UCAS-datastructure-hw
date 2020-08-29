#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//邻接表为graph[][]





int main()
{
    int *vertex;
    int  **graph;
    int dat,tad,wid;
    char c;
    scanf("%d%c",&dat,&c);
    //动态申请二维数组
    graph = (int **)malloc(sizeof(int *)*(dat+2));
    for(int i=0;i<dat+2;i++){
        graph[i] = (int *)malloc(sizeof(int)*(dat+2));
        memset(graph[i],0,(dat+2)*sizeof(int));
    }
    vertex = (int *)malloc(sizeof(int)*(dat+2));
    memset(vertex,0,(dat+2)*sizeof(int));
    wid = dat;

    scanf("%d",&dat);

    while(scanf("%d%c%d",&dat,&c,&tad)==3){
        graph[dat][tad] = 1;
        vertex[dat] = vertex[tad] = 1;
        getchar();
    }

    //output
    int diyi=1;
    for(int i=0;i<wid+1;i++){
        if(!vertex[i])
            continue;
        int first=1;
        if(diyi==0)
            printf("\n");
        diyi=0;
        printf("%d",i);

        for(int j=wid;j>=0;j--){
            if(graph[i][j]!=0){
                printf("%c",first?' ':',');
                printf("%d",j);
                first=0;
            }
        }
    }
    return 0;
}