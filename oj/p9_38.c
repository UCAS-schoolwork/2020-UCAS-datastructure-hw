#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define NONE -99999
#define SPACE 300
typedef int ElemType;

typedef struct BiNode{
    ElemType data;
    int num;
    struct BiNode *lchild, *rchild;
} Binode,BiTree;

//
ElemType Layer1[SPACE];
int sp1;
ElemType Layer2[SPACE];
int sp2;

//Convert Layer to Link
void Convert(BiTree * Bi,int num, ElemType * Layer, int sp)
{
    int lnum=2*num;
    if(lnum>=sp||Layer[lnum]==NONE)
        Bi->lchild = NULL;
    else {
        Binode * p = (Binode *)malloc(sizeof(Binode));
        Bi->lchild = p;
        p->num = 1;
        Bi->lchild->data = Layer[lnum];
        Convert(Bi->lchild,lnum,Layer,sp);
    }
    int rnum=lnum+1;
    if(rnum>=sp||Layer[rnum]==NONE)
        Bi->rchild = NULL;
    else {
        Binode * p = (Binode *)malloc(sizeof(Binode));
        Bi->rchild = p;
        p->num = 1;
        Bi->rchild->data = Layer[rnum];
        Convert(Bi->rchild,rnum,Layer,sp);
    }
    return;
}


void InputBi(ElemType * Layer, int * sp)
{
    *sp = 1;
    //Input
    char c;
    while((c=getchar())!=EOF && c!=';')
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
            for(;*sp!=1&&Layer[*sp/2]==NONE;(*sp)++)
                Layer[*sp]=NONE;
            Layer[(*sp)++] = sum;
            if(c==';')
                break;
        }
        else if(c=='n'){
            for(;*sp!=1&&Layer[*sp/2]==NONE;(*sp)++)
                Layer[*sp]=NONE;
            Layer[(*sp)++] = NONE;
        }
       
    }
}

int AddNode(Binode * Bi, ElemType e,int num)
{
    if(Bi->data == e){
        Bi->num+=num;
        return 0;
    }
    else if(Bi->data > e){
        if(!Bi->lchild){
            Binode * p = (Binode *)malloc(sizeof(Binode));
            p->lchild = p->rchild = NULL;
            p->num = num;
            p->data = e;
            Bi->lchild = p;
            return 1;
        }
        else 
            return AddNode(Bi->lchild,e,num); 
    }
    else {
        if(!Bi->rchild){
            Binode * p = (Binode *)malloc(sizeof(Binode));
            p->lchild = p->rchild = NULL;
            p->num = num;
            p->data = e;
            Bi->rchild = p;
            return 1;
        }
        else 
            return AddNode(Bi->rchild,e,num); 
    }
}
void Middle(Binode *Bi)
{
    if(!Bi)
        return ;
    Middle(Bi->lchild);
    for(int i=0;i<Bi->num;i++)
        Layer1[sp1++] = Bi->data;
    Middle(Bi->rchild);
}
void Travel(Binode *Bi,Binode * p)
{
    if(!Bi)
        return;
    AddNode(p,Bi->data,Bi->num);
    Travel(Bi->lchild,p);
    Travel(Bi->rchild,p);
}
int main()
{
    InputBi(Layer1,&sp1);
    InputBi(Layer2,&sp2);
   
    //Convert
    Binode B1,B2;
    B1.data = Layer1[1];
    B1.num = B2.num = 1;
    B2.data = Layer2[1];
    Convert(&B1, 1,Layer1,sp1);
    Convert(&B2, 1,Layer2,sp2);
    //
    Travel(&B2,&B1);
    sp1 = 1;
    Middle(&B1);
    for(int i=1;i<sp1;i++)
        printf("%d%c",Layer1[i],i==sp1-1?'\n':',');

    return 0;
}