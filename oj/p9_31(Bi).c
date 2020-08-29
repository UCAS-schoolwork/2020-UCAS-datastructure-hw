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

int compare(ElemType a, ElemType b, int mode){
    if(mode)
        return a>=b;
    else 
        return a<=b;
}
//mode==0 <=
int isBST(Binode * Bi,int mode, int dir, int bound)
{
    //dir==1 left; dir==2 right
    if(!Bi)
        return 1;
    if(Bi->lchild){
        if(compare(Bi->data,Bi->lchild->data,mode) || !isBST(Bi->lchild,mode,1,Bi->data))
            return 0;
        if(dir==2 && compare(Bi->lchild->data,bound,mode))
            return 0;
    }
    if(Bi->rchild){
        if(compare(Bi->data,Bi->rchild->data,!mode) || !isBST(Bi->rchild,mode,2,Bi->data))
            return 0;
        if(dir==1 && compare(Bi->rchild->data,bound,!mode))
            return 0;
    }

    return 1;   
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

    printf("%d",isBST(&Bi,1,0,0) || isBST(&Bi,0,0,0));

    return 0;
}