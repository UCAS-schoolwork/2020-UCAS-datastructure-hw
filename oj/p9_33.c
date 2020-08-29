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

void PrintLarge(Binode *Bi, ElemType x)
{
    if(!Bi)
        return;
    if(Bi->rchild)
        PrintLarge(Bi->rchild,x);
    if(Bi->data>=x){
        Layer[sp++] = Bi->data;
    }
    if(Bi->lchild)
        PrintLarge(Bi->lchild,x);
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
    int x;
    scanf("%d",&x);
   
    //Convert
    Binode Bi;
    Bi.data = Layer[1];
    Convert(&Bi, 1);
    //
    sp=1;
    PrintLarge(&Bi,x);
    for(int i=1;i<sp;i++)
        printf("%d%c",Layer[i],i==sp-1?'\n':',');

    return 0;
}