#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//静态链表插入排序和重排
typedef int ElemType;
#define SIZE 100
typedef struct{
    ElemType rc;
    int next;
}SLnode;

typedef struct{
    SLnode r[SIZE];
    int len;
}SLlist;

SLlist * InitSL(void)
{
    SLlist * L = (SLlist *)malloc(sizeof(SLlist));
    memset(L,0,sizeof(SLlist));
    L->r[0].rc = 0x7fffffff;
    return L;
}

void Arrange(SLlist *L)
{
    int p=L->r[0].next;
    for (int i=1; i<L->len; i++) {
        while (p<i) 
            p=L->r[p].next;
        int q=L->r[p].next;
        if (p!=i) {
            SLnode t;
            t=L->r[p];
            L->r[p]=L->r[i];
            L->r[i]=t;
            L->r[i].next=p;
        }
        p=q;
    }
}

void SL_insertsort(SLlist *L)
{
    if(L->len<=1)
        return;
    L->r[0].next = 1;
    L->r[1].next = 0;
    for(int i=2;i<=L->len;i++){
        int j;
        for(j=0;L->r[j].next!=0;j=L->r[j].next){
            if(L->r[L->r[j].next].rc>=L->r[i].rc)
                break;
        }
        L->r[i].next = L->r[j].next;
        L->r[j].next = i;
    }
    Arrange(L);
}
void Insert(SLlist *L, ElemType e)
{
    L->r[++L->len].rc = e;
}
int main()
{
    SLlist * L = InitSL();
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2){
        Insert(L,dat);
    }
    
    SL_insertsort(L);

    for(int i=1;i<=L->len;i++)
        printf("%d%c",L->r[i].rc,i==L->len?'\n':',');
    return 0;
}