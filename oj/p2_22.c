#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef char Status;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}Link;

typedef struct{
    Link * head,*tail;
    int len;
} LinkList;

LinkList * InitList()
{
    LinkList *L;
    L = (LinkList *)malloc(sizeof(LinkList));
    if(!L)
        return NULL;
    Link* p;
    p = (Link*)malloc(sizeof(Link));
    if(!p)
        return NULL;
    p->next=NULL;
    L->head = L->tail = p;
    L->len = 0;
    return L;
}

//
Status InsLast(LinkList *L,ElemType e)
{
    Link *s = (Link*)malloc(sizeof(Link));
    if(!s)
        return FALSE;
    s->data = e;
    s->next=NULL;
    L->len++;
    L->tail->next=s;
    L->tail=s;
    return TRUE;
}

//
Status PrintLink(LinkList *L)
{
    Link *p=L->head->next;
    if(!p)
        printf("NULL\n");
    else  {
        for(;p->next;p=p->next)
            printf("%c,",p->data);
        printf("%c",p->data);
    }
    return TRUE;
}

int main()
{
    LinkList *L=InitList();
    char dat;
    char c;
    while(scanf("%c%c",&dat,&c)==2)
        InsLast(L,dat);

    Link *p=L->head->next;
    Link *s;
    L->head->next=NULL;
    for(;p;){
        s=p;
        p=p->next;
        s->next=L->head->next;
        L->head->next=s;
    }
    PrintLink(L);
    return 0;
}