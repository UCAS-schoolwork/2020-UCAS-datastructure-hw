//边界标志+首次适配
//题目指定了地址，所以用int变量模拟地址

#include <stdio.h>
#include <stdlib.h>

typedef struct WORD{
    int tag; //1:allocated; 0:vice versa
    int addr;
    struct WORD *llink;
    struct WORD *rlink;
}Word,Space;

Space *pav;

int AddBound(int addr,int tag)
{
    Space *p = (Space *)malloc(sizeof(Word));
    p->addr = addr;
    p->tag = tag;
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
    p->addr = -1;
    p->tag = 2;
    return p;
}

void PrintLink(Space *p,int cellsize)
{
    int addr,size;
    addr = -1;
    size = 0;
    if(!p)
        printf("0 0 0");
    else{
        for(;p;p=p->rlink){
            if(p->tag == 0){
                if(!size)
                    addr = p->addr;
                size += cellsize;
            }
            else{
                if(size)
                    printf("0 %d %d\n",addr, size);
                size = 0;
            }
        }
        if(size)
            printf("0 %d %d\n",addr, size);
    }
    if(addr == -1)
         printf("0 0 0");
}

int main()
{
    Space * B = InitBound();
    pav = B;
    int highbound,lowbound,cellsize;
    scanf("%d%d%d",&lowbound,&highbound,&cellsize);
    int tag,addr;
    addr = lowbound;
    while(scanf("%d",&tag)==1){
        AddBound(addr,tag);
        addr += cellsize;
    }
    PrintLink(B->rlink,cellsize);
    return 0;
} 