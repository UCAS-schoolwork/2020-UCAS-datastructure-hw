#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int ElemType;
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
            printf("%d,",p->data);
        printf("%d",p->data);
    }
    return TRUE;
}
// Move *(s+1) to the rear of *h
Status MoveAfter(LinkList* L,Link *h, Link *s)
{
    if(h->next==s->next)
        return TRUE;
    if(!s->next)
        return FALSE;
    Link *p = s->next->next;
    s->next->next = h->next;
    if(!h->next)
        L->tail = s;
    h->next = s->next;
    s->next = p;
    return TRUE;
}
int main()
{
    LinkList *L=InitList();
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2)
        InsLast(L,dat);
    Link *p;
    for(p=L->head;p&&p->next;p=p->next){
        Link  maxn;
        maxn.data=INT_MAX;
        for(Link *q=p;q->next!=NULL;q=q->next){
            if(q->next->data<maxn.data){
                maxn.data = q->next->data;
                maxn.next = q;
            }
        }
        MoveAfter(L,p,maxn.next);
    }
    PrintLink(L);

    return 0;
}