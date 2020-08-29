#include <stdio.h>

int L[200];
int R[200];

int Visit(int u,int v)
{
    if(!v)
        return 0;
	if(u==v)
        return 1;
    if(Visit(u,L[v]))
        return 1;
    if(Visit(u,R[v]))
        return 1;
    return 0;
}

int main()
{
    int dat,sl,sr,u,v;
    sl=sr=0;
    char c;
    while(scanf("%d%c",&dat,&c)==2){
        L[sl++] = dat;
        if(c==';')
            break;
    }
    while(scanf("%d%c",&dat,&c)==2){
        R[sr++] = dat;
        if(c==';')
            break;
    }
    scanf("%d%c",&u,&c);
    scanf("%d%c",&v,&c);
    if(u==v)
        printf("0");
    else 
        printf("%d",Visit(u,v));
    return 0;
}