#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef char Status;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
    struct LNode *succ;
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
Link *LocatePos(LinkList *L,int i)
{
    Link* cur = L->head;
    for(int j=1;cur&&j<=i;j++){
        cur=cur->next;
    }
    return cur;
}

int snext[199];

void GenNextval(LinkList *K, int *s)
{
    int i=1;
    s[1] = 0;
    int j=0;
    while(i<K->len){
        Link *pi, *pj;
        pi = LocatePos(K,i);
        pj = LocatePos(K,j);
        if(j==0||pi->data == pj->data){
            ++i;
            ++j;
            if(pi->next->data!=pj->next->data)
                s[i] = j;
            else
                s[i] = s[j];
        }
        else 
            j = s[j];
    }
}


void GenNext(LinkList *K)
{
    Link *pj = K->head;
    Link *pi = pj->next;
    pi->succ = pj->succ = pj;
    while(pi && pi->next){
        if(pj == K->head || pi->data == pj->data){
            pi = pi->next;
            pj = pj->next;
            if(pi->data!=pj->data)
                pi->succ = pj;
            else
                pi->succ = pj->succ;
        }
        else
            pj = pj->succ;
    }
    return;
}

int KMP(LinkList *L, LinkList *K, int pos)
{
 
    int i=pos;
    int j=1;
    Link *pi = LocatePos(L,i);
    Link *pj = LocatePos(K,j);
    while(i<=L->len && j<=K->len){

        if(j==0 || pi->data == pj->data){
            ++i;
            pi = pi->next;
            ++j;
            pj = pj->next;
        }
        else {
            j = snext[j];
            pj = pj->succ;
        }
    }
    if(j>K->len)
        return i - K->len;

    return 0;
}

int main()
{
    LinkList *L=InitList();
    LinkList *K = InitList();

    char c;
    while((c=getchar())!='\n')
        InsLast(L,c);
    while((c=getchar())!=EOF && c!='\n')
        InsLast(K,c);
    GenNext(K);
    GenNextval(K,snext);
    
    int pos = 1;
    int location;
    int first = 0;
    while((location = KMP(L,K,pos))>0){
        if(first)
            printf(" ");
        first = 1;
        printf("%d",location);
        pos = location+1;
    }
    printf("\n");
    for(int i=1;i<=K->len;i++)
        printf("%d%c",snext[i],i==K->len?'\n':' ');
    return 0;
   
}