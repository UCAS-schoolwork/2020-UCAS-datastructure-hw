//若待排序元素存于链表中，可以先将其复制进数组，然后就可以使用快速排序了。
//若复制记录的消耗大，可以先对关键字排序，再折半找到对应的记录，并复制。

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 20000
#define TRUE 1
#define FALSE 0

typedef struct{
    int key;
    int rc;
}DataNode;

typedef DataNode ElemType;
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

DataNode s[MAXSIZE];
int sp;

void swp(DataNode *a, DataNode *b)
{
    DataNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void quicksort(DataNode a[], DataNode b[])
{
    if (a >= b)
        return;
    else if(a == b - 1 && a->key>b->key){
        swp(a,b);
        return;
    }
    DataNode *last = a;
    DataNode *index = a + 1;
    swp(a+(b-a)/2,a);
    for (; index <= b; index++)
    {
        if (index->key < a->key)
            swp(index, ++last);
    }
    swp(last, a);
    quicksort(a, last-1);
    quicksort(last + 1, b);
}


int main()
{
    LinkList *L=InitList();
    int dat;
    char c;
    
    DataNode data;
    while(scanf("%d",&dat)==1){
        data.key = dat;
        InsLast(L,data);
    }
    
    Link *p = L->head->next;
    while(p=p->next){
        s[sp].key = p->data.key;
        sp++;
    }
    
    quicksort(s,s+sp-1);

    for(int i=0;i<sp;i++)
        printf("%d%c",s[i],i==sp-1?'\n':' ');

    return 0;
}