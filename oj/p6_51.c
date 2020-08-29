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
int Prior(int a, int b)
{
    a=-a;
    b=-b;
    if((a=='+'||a=='-')&&(b=='*'||b=='/'||b=='-'))
        return 1;
    return 0;
}
void PrintFml(Binode *Bi)
{
    if(Bi){
        if(Bi->lchild){
            if(Prior(Bi->lchild->data,Bi->data)){
                printf("(");
                PrintFml(Bi->lchild);
                printf(")");
            }
            else 
                PrintFml(Bi->lchild);
        }
        if(Bi->data<0)
            printf("%c",-Bi->data);
        else 
            printf("%d",Bi->data);
        if(Bi->rchild){
            if(Prior(Bi->rchild->data,Bi->data)){
                printf("(");
                PrintFml(Bi->rchild);
                printf(")");
            }
            else 
                PrintFml(Bi->rchild);
        }
    }
}
int isOP(char c)
{
    if(c=='+'||c=='-'||c=='*'||c=='/')
        return 1;
    return 0;
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
           
        }
        else if(c=='n'){
            Layer[sp++] = NONE;
        }
        else if(isOP(c))
            Layer[sp++] = -c;
    }
   
    //Convert
    Binode Bi;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    PrintFml(&Bi);

    return 0;
}