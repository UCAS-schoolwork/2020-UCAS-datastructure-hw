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
//HeadPos is regarded as the 0th Pos
Link *LocatePos(LinkList *L,int i)
{
    Link* cur = L->head;
    for(int j=1;cur&&j<=i;j++){
        cur=cur->next;
    }
    return cur;
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
Status Deli(LinkList *L,int i)
{
    Link *p;
    if(i<1||(p=LocatePos(L,i-1))==NULL||!p->next)
        return FALSE;
    Link *s=p->next->next;
    free(p->next);
    p->next=s;
    if(!s)
        L->tail=p;
    L->len--;
    return TRUE;
}

//
Status PrintLink(LinkList *L)
{
    Link *p=L->head->next;
    if(!p)
        printf("NULL\n");
    else  
        for(int i=0;i<L->len;i++){
            printf("%d%c",p->data,i==L->len-1?'\n':' ');
            p=p->next;
        }
    return TRUE;
}

int main()
{
    int i,j;
    scanf("%d%d",&j,&i);
    LinkList *L=InitList();
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2)
        InsLast(L,dat);
    Deli(L,i+1);
    PrintLink(L);
    return 0;
}