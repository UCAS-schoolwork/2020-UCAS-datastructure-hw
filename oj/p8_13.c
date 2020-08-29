//边界标志+首次适配
//题目指定了地址，所以用int变量模拟地址

#include <stdio.h>
#include <stdlib.h>

typedef struct WORD{
    int tag; //1:allocated; 0:vice versa
    int size;
    int addr;
    struct WORD *llink;
    struct WORD *rlink;
}Word,Space;

Space *pav;

int AddBound(int addr, int size)
{
    Space *p = (Space *)malloc(sizeof(Word));
    p->addr = addr;
    p->size = size;
    p->llink = pav;
    p->rlink = pav->rlink;
    pav->rlink = p;
    pav = p;
    return 1;
}
Space * InitBound()
{
    Space *p = (Space *)malloc(sizeof(Word));
    p->llink = p->rlink = NULL;
    p->size = 0;
    p->addr = -1;
    p->tag = 2;
    return p;
}
int DelSpace(Space *p)
{
    p->llink->rlink = p->rlink;
    if(p->rlink)
        p->rlink->llink = p->llink;
    free(p);
    return 1;
}
int Recycle(int addr, int size)
{
    for(;pav&&pav->rlink;pav = pav->rlink){
        if(pav->addr<addr && pav->rlink->addr>addr)
            goto FIND;
    }
    if(pav->addr+pav->size==addr)
        pav->size+=size;
    else
        AddBound(addr,size);
    return 1;
FIND:
    if(pav->addr+pav->size==addr){
        if(addr+size==pav->rlink->addr){
            pav->size+=size+pav->rlink->size;
            DelSpace(pav->rlink);
        }
        else
            pav->size+=size;    
    }
    else{
        if(addr+size==pav->rlink->addr){
            pav->rlink->addr-=size;
            pav->rlink->size+=size;
        }
        else
            AddBound(addr,size); 
    }
    return 1;
}
void PrintLink(Space *p)
{
    for(;p;p=p->rlink)
        printf("0 %d %d\n",p->addr, p->size);
}
int main()
{
    Space * B = InitBound();
    pav = B;
    int dat1,dat2,dat3;
    int first = 1;
    while(scanf("%d%d%d",&dat1,&dat2,&dat3)==3){
        if(!dat1)
            AddBound(dat2,dat3);
        else {
            if(first){
                pav = B;
                first = 0;
            }
            Recycle(dat2,dat3);
        }
    }
    PrintLink(B->rlink);
    return 0;
}