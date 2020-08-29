#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef int ElemType;
typedef char Status;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
    struct LNode *pre;
    int freq;
    int seq;
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
    p->next=p->pre=p;
    L->head = L->tail = p;
    L->len = 0;
    return L;
}
//HeadPos is regarded as the 0th Pos
Link *LocatePos(LinkList *L,int i)
{
    Link* cur = L->head;
    for(int j=1;cur&&j<=i;j++){
        cur=cur->next;
    }
    cur->freq++;
    return cur;
}
Link *Locate(LinkList *L,ElemType e)
{
    Link* cur = L->head;
    for(int j=1;cur&&cur->data!=e;j++){
        cur=cur->next;
    }
    cur->freq++;
    return cur;
}
//
Status InsLast(LinkList *L,ElemType e)
{
    Link *s = (Link*)malloc(sizeof(Link));
    if(!s)
        return FALSE;
    s->data = e;
    s->freq=0;
    s->seq=0;
    s->next=L->head;
    s->pre=L->tail;
    L->len++;
    L->tail->next=s;
    L->tail=s;
    L->head->pre=s;
    return TRUE;
}

//
Status PrintLink(LinkList *L)
{
    Link *p=L->head->next;
    if(!p)
        printf("NULL\n");
    else  {
        for(;p->next!=L->head;p=p->next)
            printf("%d ",p->data);
        printf("%d",p->data);
    }
    return TRUE;
}
//复杂度O(n)
int main()
{
    LinkList *L=InitList();
    int dat;
    char c;
    scanf("%d",&dat);
    while(scanf("%d%c",&dat,&c)==2){
        InsLast(L,dat);
        if(c=='\n')
            break;
    }
    Link *p;
    int seq=1;
    while(scanf("%d%c",&dat,&c)==2){
        p=Locate(L,dat);
        if(p->seq==0)
            p->seq = seq;
        Link *s=p->pre;
        for(;s->freq<p->freq&&s!=L->head;s=s->pre)
            ;
        for(;s->freq==p->freq&&s->seq>=p->seq&&s!=L->head;s=s->pre)
            ;
        p->pre->next=p->next;
        p->next->pre=p->pre;
        s->next->pre=p;
        p->next=s->next;
        s->next=p;
        p->pre=s;
        seq++;
    }
    PrintLink(L);
    return 0;
}