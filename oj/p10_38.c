#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXSIZE 20000
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
Status PrintLink(Link *L)
{
    Link *p=L;
    if(!p)
        printf("NULL\n");
    else  {
        for(;p->next;p=p->next)
            printf("%d ",p->data);
        printf("%d",p->data);
    }
    return TRUE;
}

Link * Merge(Link* A, Link* B) //A<B
{
    if(!A)
        return B;
    else if(!B)
        return A;
    Link *p, *q;
    if(A->data<B->data){
        p=A;
        q=B;
    }
    else {
        p=B;
        q=A;
    }
    Link *rt = p;
    while(p->next&&q){
        if(p->next->data<=q->data)
            p=p->next;
        else{
            Link *r = q;
            q=q->next;
            r->next = p->next;
            p->next = r;
            p = p->next;
        }
    }
    if(!p->next)
        p->next = q;
    return rt;
}

Link *s[MAXSIZE];
int sp;

int Mergesort(Link * s[])
{
    int last, fa;
    last=fa=0;
    Link *p;
    while(sp>1){
        while(fa<sp){
            if(fa+1<sp)
                p = Merge(s[fa],s[fa+1]);
            else 
                p = s[fa];
            fa+=2;
            s[last++] = p;
        }
        
        sp=last;
        for(int i=0;i<sp;i++)
      
        fa=last=0;
        
    }
    return 1;
}
//把分段的指针存到数组里
int Pre_Merge(LinkList *L)
{
    Link *p,*q;
    for(p=L->head->next;p;){
        s[sp++] = p;
        while(p->next && p->data<p->next->data)
            p=p->next;
        q=p;
        p=p->next;
        q->next = NULL;
    }
    return 1;
}

int main()
{
    LinkList *L=InitList();
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2)
        InsLast(L,dat);
    Link *p;
    Pre_Merge(L);
    Mergesort(s);

    PrintLink(s[0]);

    return 0;
}