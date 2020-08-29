//边界标志+首次适配
//题目指定了地址，所以用int变量模拟地址

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXK 30

typedef struct WORD{
    int tag; //1:allocated; 0:vice versa
    int addr;
    struct WORD *llink;
    struct WORD *rlink;
}Word,Space;

typedef struct HEAD{
    int nodesize;
    struct WORD * first;
}Head;

Space *pav;
Head Partner[MAXK];

int AddBound(int addr, int k)
{
    Space *p = (Space *)malloc(sizeof(Word));
    p->addr = addr;
    p->llink = pav;
    p->rlink = pav->rlink;
    pav->rlink = p;
    pav = p;
    return 1;
}
void InitBound(int k)
{
    Space *p = (Space *)malloc(sizeof(Word));
    p->llink = p->rlink = NULL;
    Partner[k].first = p;
    p->addr = -1;
    p->tag = 2;
}
int DelSpace(Space *p)
{
    p->llink->rlink = p->rlink;
    if(p->rlink)
        p->rlink->llink = p->llink;
    free(p);
    return 1;
}
int Recycle(int addr, int k)
{
    pav = Partner[k].first;
    int size = 1<<k;
    for(;pav&&pav->rlink;pav = pav->rlink){
        if(pav->addr<addr && pav->rlink->addr>addr)
            goto FIND;
    }
    if(!(addr%(2<<k)))//partner in the right
        AddBound(addr,k);
    else 
        goto LEFT;
    return 1;
FIND:
    if(!(addr%(2<<k))){ //partner in the right
        if(addr+size==pav->rlink->addr){
            DelSpace(pav->rlink);
            Recycle(addr,k+1);
        }
        else
            AddBound(addr,k); 
    }
    else{ //partner in the left
LEFT:
        if(pav->addr+size == addr){
            Space *p = pav;
            pav = pav->rlink;
            DelSpace(p);
            Recycle(addr-size,k+1);
        }
        else
            AddBound(addr,k); 
    }
    return 1;
}
void PrintLink(void)
{
    for(int i=0;i<MAXK;i++){
        Space *p = Partner[i].first->rlink;
        if(!p)
            continue;
        printf("%d",i);
        for(;p;p=p->rlink)
            printf(" %d",p->addr);
        printf("\n");
    }
}

int getint(void)
{
    char c;
    while((c=getchar())!=EOF)
    {
        if(c=='\n')
            return -1;
        int sum=0;
        if(isdigit(c)){
            sum = c-'0';
            while (isdigit(c=getchar())){
                sum*=10;
                sum+=c-'0';
            }
            
            return sum;
        }
    }
    return -1;
}
int main()
{
    for(int i = 0;i<MAXK;i++)
        InitBound(i);
    int k,addr;
    int mode = 1;
    char c;
    while((c=getchar())!=EOF)
    {
        int sum=0;
        if(c=='\n'){
            if(mode == 1)
                mode =3;
            else if(mode == 3)
                break;
        }
        else if(isdigit(c)){
            sum = c-'0';
            while (isdigit(c=getchar())){
                sum*=10;
                sum+=c-'0';
            }
                if(mode==1||mode==3){
                    k = sum;
                    pav = Partner[k].first;
                }
                else if(mode==2)
                    AddBound(sum,k);
                else if(mode==4)
                    Recycle(sum,k);
                if(mode == 1)
                    mode = 2;
                else if(mode == 2 && c=='\n')
                    mode = 1;
                else if(mode == 3)
                    mode = 4;
                else if(mode == 4 && c=='\n')
                    mode = 3;
        }
    }

 
    PrintLink();
    return 0;
}