#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef char Status;
typedef struct LNode{
    ElemType key;
    struct LNode *next;
}Link;

Link *h, *t;

Status InsLast(ElemType e)
{
    Link *p = (Link *)malloc(sizeof(Link));
    if(t)
        t->next = p;
    else {
        h = p;
        t = h;
    }
    p->key = e;
    p->next = h;
    t = p;
    return TRUE;
}

void findAndPrint(ElemType e)
{
    printf("%d",t->key);
    if(t->key==e)
        return;
    else if(t->key>e)
        t = t==h? h->next : h;
    else 
        t = t->next;
    for(;;t=t->next){
        printf(",%d",t->key);
        if(t->key==e)
            break;
    }
    return;
}

int main()
{
    int dat;
    char c;
    t = h = NULL;
    while(scanf("%d%c",&dat,&c)==2){
        InsLast(dat);
        if(c==';')
            break;
    }
    t = h;
    while(scanf("%d%c",&dat,&c)==2){
        findAndPrint(dat);
        if(c==',')
            printf(";");
    }
    return 0;
}