#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE -99999
#define SPACE 300
typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    struct BiNode *lchild, *rchild;
} Binode,BiTree;

int first[SPACE];
int middle[SPACE];
int last[SPACE];
int fsp,msp,lsp;

Binode * Gen(int f1,int f2,int m1,int m2)
{
    Binode * p;
    p = (Binode *)malloc(sizeof(Binode));
    p->data = first[f1];
    if(f1==f2){
        p->lchild = NULL;
        p->rchild = NULL;
        return p;
    }
    int i;
    for(i=m1;i<=m2;i++){
        if(first[f1]==middle[i])
            break;
    }
    if(i==m1){
        p->lchild = NULL;
        p->rchild = Gen(f1+1,f2,m1+1,m2);
    }
    else if(i==m2){
        p->rchild = NULL;
        p->lchild = Gen(f1+1,f2,m1,m2-1);
    }
    else {
        p->lchild = Gen(f1+1,f1+i-m1,m1,i-1);
        p->rchild = Gen(f1+i-m1+1,f2,i+1,m2);
    }
    return p;
}

void PrintLast(Binode *Bi)
{
    if(Bi->lchild)
        PrintLast(Bi->lchild);
    if(Bi->rchild)
        PrintLast(Bi->rchild);
    last[lsp++] = Bi->data;
    return;
}
int main()
{
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2){
        first[fsp++] = dat;
        if(c==';') 
            break;
    }
    while(scanf("%d%c",&dat,&c)==2)
        middle[msp++] = dat;
    Binode * p = Gen(0,fsp-1,0,msp-1);
    PrintLast(p);
    for(int i=0;i<lsp;i++)
        printf("%d%c",last[i],i==lsp-1?'\n':',');
    return 0;
}

