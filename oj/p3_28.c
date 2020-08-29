#include <stdio.h>
#include <stdlib.h>
//Quene by Circular Link
typedef int ElemType;
typedef struct QNode{
    ElemType data;
    struct QNode * next;
}Link;
typedef struct Quene{
    Link * tail;
}Quene;

Quene * InitQuene()
{
    Quene *Q;
    Q = (Quene*)malloc(sizeof(Quene));
    Q->tail=NULL;
    return Q;
}
//If we do not set a head node or  a tail node, 2 or 3 cases should be discussed.
int InQuene(Quene *Q,ElemType e)
{
    Link * p = (Link*)malloc(sizeof(Link));
    if(!Q->tail){
        p->next=p;
        Q->tail=p;
    }
    else{
        p->next = Q->tail->next;
        Q->tail->next = p;
        Q->tail=p;
    }
    p->data = e;
    return 1;
}

ElemType OutQuene(Quene *Q)
{
    ElemType e;
    Link *p;
    if(!Q->tail)
        e=0;
    else if(Q->tail->next!=Q->tail){
        e = Q->tail->next->data;
        p = Q->tail->next->next;
        free(Q->tail->next);
        Q->tail->next = p;
    }
    else {
        e = Q->tail->data;
        free(Q->tail);
        Q->tail = NULL;
    }
    return e;
}

int main()
{
    char c;
    int d;
    Quene *Q = InitQuene();
    scanf("%d",&d);
    while(scanf("%d%c",&d,&c)==2){
        InQuene(Q,d);
    }
    while(Q->tail!=Q->tail->next){
        printf("%d,",OutQuene(Q));
    }
    printf("%d",OutQuene(Q));
    return 0;
}
