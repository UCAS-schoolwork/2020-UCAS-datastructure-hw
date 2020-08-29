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


int main()
{
    LinkList * L1=InitList();
    LinkList * L2=InitList();
    char c;
    int dat;
    while((c=getchar())!='\n')
        ;
    while(scanf("%d%c",&dat,&c)==2)
    {
        InsLast(L1,dat);
        if(c=='\n')
            break;
    }
    while(scanf("%d%c",&dat,&c)==2)
    {
        InsLast(L2,dat);
    }
    int m=L1->len;
    int n=L2->len;
    if(m<n)
        L1->tail->next = L2->head->next;
    else
        L2->tail->next = L1->head->next;
    //如果设了尾指针其实不用非把长的接到短的后面
    Link *ha=L1->head;
    Link *hb=L2->head;
    Link *hc = m<n?L1->head:L2->head;
    Link *p=m<n?ha->next:hb->next;
    for(int i=0;i<m+n;i++){
        printf("%d%c",p->data,i==m+n-1?'\n':' ');
        p=p->next;
    }
    return 0;
}
