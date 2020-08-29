#include <stdio.h>

int L[200];
int R[200];
int T[200];
int sl,sr;

int Visit(int u,int v)
{
    if(!u || !v)
        return 0;
    if(T[u]==v)
        return 1;
    else if(Visit(T[u],v))
        return 1;
    return 0;
}

int findP(int i)
{
    for(int j=1;j<sl;j++){
        if(L[j]==i)
            return j;
    }
    for(int j=1;j<sr;j++){
        if(R[j]==i)
            return j;
    }
    return 0;
}

int main()
{
    int dat,u,v;
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

    T[0]=0;
    for(int i=1;i<sl;i++)
    {
        T[i]=findP(i);
    }

    printf("%d",Visit(u,v));
    return 0;
}