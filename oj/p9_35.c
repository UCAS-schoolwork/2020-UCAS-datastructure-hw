#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE -99999
#define SPACE 300
typedef int ElemType;

typedef struct BiNode{
    int Ltag,Rtag; 
    ElemType data;
    struct BiNode *lchild, *rchild;
} Binode,BiTree;

//
ElemType Layer[SPACE];
int sp;

//Convert Layer to Link
void Convert(BiTree * Bi,int num)
{
    int lnum=2*num;
    if(lnum>=sp||Layer[lnum]==NONE)
        Bi->lchild = NULL;
    else {
        Binode * p = (Binode *)malloc(sizeof(Binode));
        Bi->lchild = p;
        p->Ltag = p->Rtag = 0;
        Bi->lchild->data = Layer[lnum];
        Convert(Bi->lchild,lnum);
    }
    int rnum=lnum+1;
    if(rnum>=sp||Layer[rnum]==NONE)
        Bi->rchild = NULL;
    else {
        Binode * p = (Binode *)malloc(sizeof(Binode));
        Bi->rchild = p;
        p->Ltag = p->Rtag = 0;
        Bi->rchild->data = Layer[rnum];
        Convert(Bi->rchild,rnum);
    }
    return;
}

Binode *pre;
void InThread(Binode *p)
{
    if(!p)
        return;
    InThread(p->lchild);
    if(!p->lchild){
        p->Ltag = 1;
        p->lchild = pre;
    }
    if(pre && !pre->rchild){
        pre->Rtag = 1;
        pre->rchild = p;
    }
    pre = p;
    InThread(p->rchild);
}

void FindAndPrint(Binode * Bi, ElemType a, ElemType b)
{
    if(!Bi)
        return ;
    if(Bi->data <= a) {
        if(!Bi->Rtag)
            FindAndPrint(Bi->rchild,a,b);
    }
    else if(a<Bi->data && Bi->data<b){
        if(!Bi->Ltag)
            FindAndPrint(Bi->lchild,a,b);
        Layer[sp++] = Bi->data;
        if(!Bi->Rtag)
            FindAndPrint(Bi->rchild,a,b);
    }
    else if(Bi->data>=b){
        if(!Bi->Ltag)
            FindAndPrint(Bi->lchild,a,b);
    }
}

int main()
{
    sp=1;
    //Input
    char c;
    while((c=getchar())!=EOF)
    {
        int sum=0;
        int sign=0;
        
        if(isdigit(c)){
            sum = c-'0';

            while (isdigit(c=getchar())){
                sum*=10;
                sum+=c-'0';
            }
            if(sign)
                sum=-sum;
            for(;sp!=1&&Layer[sp/2]==NONE;sp++)
                Layer[sp]=NONE;
            Layer[sp++] = sum;
            if(c==';')
                break;
           
        }
        else if(c=='n'){
            for(;sp!=1&&Layer[sp/2]==NONE;sp++)
                Layer[sp]=NONE;
            Layer[sp++] = NONE;
        }
        if(c==';')
            break;
       
    }
    int a,b;
    scanf("%d%c%d",&a,&c,&b);
    //Convert
    Binode Bi;
    Bi.Ltag = Bi.Rtag = 0;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    pre = NULL;
    InThread(&Bi);
    sp = 1;
    FindAndPrint(&Bi,a,b);
    for(int i=1;i<sp;i++)
        printf("%d%c",Layer[i],i==sp-1?'\n':',');
    return 0;
}