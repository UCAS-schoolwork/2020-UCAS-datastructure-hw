#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE -99999
#define SPACE 300
typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    struct BiNode *lchild, *rchild;
    //lchild == firstchild; rchild == nextsibling
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

void PrintAO(Binode * Bi, int i)
{
    if(Bi){
        for(int j=0;j<i;j++)
            printf(" ");
        if(Bi->data<0)
            printf("%c\n",-Bi->data);
        else 
            printf("%d\n",Bi->data);
        PrintAO(Bi->lchild,i+1);
        PrintAO(Bi->rchild,i);
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
        if(c>='A'&&c<='Z'){
            
            for(;sp!=1&&Layer[sp/2]==NONE;sp++)
                Layer[sp]=NONE;
            Layer[sp++] = -c;
        }
      
        else if(isdigit(c)){
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
            for(;sp!=1&&Layer[sp/2]==NONE;sp++)
                Layer[sp]=NONE;
            Layer[sp++] = NONE;
        }
    }
   
    //Convert
    Binode Bi;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    PrintAO(&Bi,0);

    return 0;
}