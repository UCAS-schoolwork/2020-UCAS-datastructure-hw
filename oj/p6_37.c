#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE 0
#define SPACE 300
typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    struct BiNode *lchild, *rchild;
} Binode,BiTree;

typedef Binode* ElemType2;
//
ElemType Layer[SPACE];
int sp;

//static stack
ElemType2 Stack[SPACE];
int tp;
ElemType2 Pop(void)
{
    if(tp>0)
        return Stack[--tp];
    else 
        return NONE;
}
int Push(ElemType2 e)
{
    if(tp>=SPACE)
        return 0;
    else 
        Stack[tp++] = e;
    return 1;
}

//Covert Layer to Link
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
        }
        else if(c=='n'){
            Layer[sp++] = NONE;
        }
    }
    //Convert
    Binode Bi;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    Binode * p = &Bi;
    while(p||tp>0){
        if(p){
            if(p!=&Bi)
                printf(",");
            printf("%d",p->data);
            Push(p->rchild);
            p=p->lchild;
        }
        else 
            p=Pop();
    }

    return 0;
}