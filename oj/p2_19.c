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
Status Delplus(LinkList *L,Link *p)
{
    if(!p->next)
        return FALSE;
    Link *s=p->next->next;
    L->len--;
    free(p->next);
    p->next=s;
    if(!s)
        L->tail=p;
    return TRUE;
}
//
Status PrintLink(LinkList *L)
{
    Link *p=L->head->next;
    for(int i=0;i<L->len;i++){
        printf("%d%c",p->data,i==L->len-1?'\n':' ');
        p=p->next;
    }
    return TRUE;
}

int main()
{
    LinkList *L=InitList();
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2)
        InsLast(L,dat);
    
    Link *p = LocatePos(L,L->len-2);
    ElemType mink=p->next->data;
    Delplus(L,p);
    ElemType maxk=p->next->data;
    Delplus(L,p);
   //单链表不能二分就只能遍历
   for(p=L->head;p->next;p=p->next){
       if(p->next->data>mink)
            break;
   }
   for(;p->next&&p->next->data<maxk;){
       Delplus(L,p);
   }

    PrintLink(L);
    return 0;
}