#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE -99999
#define SPACE 600
typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    int Ltag,Rtag;
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
        Bi->lchild->data = Layer[lnum];
        Convert(Bi->lchild,lnum);
    }
    int rnum=lnum+1;
    if(rnum>=sp||Layer[rnum]==NONE)
        Bi->rchild = NULL;
    else {
        Binode * p = (Binode *)malloc(sizeof(Binode));
        Bi->rchild = p;
        Bi->rchild->data = Layer[rnum];
        Convert(Bi->rchild,rnum);
    }
    return;
}

Binode * findP(Binode *Bi, int num)
{
    Binode * p;
    if(Bi){
        if(Bi->data == num)
            return Bi; 
        p = findP(Bi->lchild,num);
        if(p)
            return p;
        p = findP(Bi->rchild,num);
        if(p)
            return p;
        return NULL;
    }
    return NULL;
}

void InsertT(Binode *Bi, Binode *Ci,int num)
{
    Binode * p;
    p = findP(Bi,num);
    if(p){
        Binode *q = p->lchild;
        p->lchild = Ci;
        Ci->rchild = q;
    }
}
void ClueInMi(Binode *Bi)
{
    if(Bi){
        ClueInMi(Bi->lchild);
        Layer[sp+1] = Bi->lchild?Bi->lchild->data:NONE;
        Layer[sp+3] = Bi->rchild?Bi->rchild->data:NONE;
        Layer[sp+4] = Bi->data;
        sp+=5;
        ClueInMi(Bi->rchild);
    }
}
void PrintT(Binode * Bi)
{
    Layer[0] = Layer[sp+4] = 0;
    for(int i=1;i<sp;i+=5){
        if(Layer[i+1]==NONE){
            Layer[i]=1;
            Layer[i+1]=Layer[i-1];
        }
        else {
            Layer[i] = 0;
        }
        if(Layer[i+3]==NONE){
            Layer[i+2]=1;
            Layer[i+3]=Layer[i+9];
        }
        else {
            Layer[i+2] = 0;
        }
    }
    for(int i=1;i<sp;i+=5){
        for(int j=0;j<4;j++)
            printf("%d%c",Layer[i+j],j==3?(i==sp-5?'\n':';'):',');
    }
}

int main()
{
    Binode Bi,Ci;
    int first=0;
NEXTTREE:
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
        else if(c==';')
            break;
    }
   
    //Convert
    if(!first){
        Bi.data = Layer[1];
        Convert(&Bi, 1);
        first=1;
        goto NEXTTREE;
    }
    Ci.data = Layer[1];
    Convert(&Ci, 1);
    int num;
    scanf("%d",&num);
    //
    InsertT(&Bi,&Ci,num);
    sp=1;
    ClueInMi(&Bi);
    PrintT(&Bi);

    return 0;
}