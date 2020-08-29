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
int findA(int u, int v)
{
    if(u==v)
        return Layer[u];
    else if(u>v)
        return findA(u/2,v);
    else 
        return findA(u,v/2);
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
        if(c=='-'){
            sign = 1;
            goto MINUS;
        }
        if(isdigit(c)){
            sum = c-'0';
MINUS:
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
            Layer[sp++] = NONE;
        }
    }
    int v1,v2;
    scanf("%d%c",&v1,&c);
    scanf("%d",&v2);
    //Convert
    Binode Bi;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    int in1,in2;
    for(in1=1;in1<sp;in1++)
        if(Layer[in1]==v1)
            break;
    for(in2=1;in2<sp;in2++)
        if(Layer[in2]==v2)
            break;
    printf("%d",findA(in1,in2));

    return 0;
}