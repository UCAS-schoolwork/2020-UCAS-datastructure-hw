#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
#define abs(a) (a<0?-(a):a)
typedef struct TERM{
    int base;
    int pow;
}Term;
typedef Term ElemType;
typedef char Status;
typedef struct LNode{
    ElemType data;
    struct LNode *next;
    struct LNode *prior;
}Link;
//双向循环链表
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
    p->next=p->prior=p;
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
    s->prior=L->tail;
    s->next=L->head;
    L->head->prior=s;
    L->len++;
    L->tail->next=s;
    L->tail=s;
    return TRUE;
}

Status Delp(LinkList *L,Link *p)
{
    p->prior->next=p->next;
    p->next->prior=p->prior;
    if(p==L->tail)
        L->tail=p->prior;
    free(p);
    L->len--;
    return TRUE;
}

//数组仅用于读取输入
Term input[1000];
int ix=0;
void addi(int base,int pow)
{
    if(!pow&&!base)
        return;
    input[ix].base=base;
    input[ix].pow=pow;
    ix++;
    
}
int cmp1(const void *a, const void *b) //use for qsort
{
	return (*(Term *)b).pow - (*(Term *)a).pow;
}
int main()
{
    int dat,pow,sign;
    dat=pow=sign=0;
    LinkList *L=InitList();
    char c;
    //输入
    while((c=getchar())!=EOF){
        if(c=='-'){
            addi(dat,pow);
            dat=pow=0;
            sign=1;
        }
        if(c=='+'){
            addi(dat,pow);
            dat=pow=0;
            sign=0;
        }
        if(isalpha(c)){
            dat=1;
            goto POW;
        }
        else if(isdigit(c)){
            dat = c-'0';
            while (isdigit(c=getchar())){
                dat*=10;
                dat+=c-'0';
            }
POW:
            if(sign)
                dat=-dat;
            if(isalpha(c)){
                pow=1;
                c=getchar();
                if(c=='^'){
                    scanf("%d",&pow);
                }      
            }
        }
            
    }
    addi(dat,pow);
    //排序
    qsort(input,ix,sizeof(Term),cmp1);
    for(int i=0;i<ix;i++){
        InsLast(L,input[i]);
    }
    Link *p;
    //合并同类项
    for(p=L->head->next;p->next!=L->head;){
        if(p->next->data.pow==p->data.pow){
            p->data.base+=p->next->data.base;
            Delp(L,p->next);
        }
        else
            p=p->next;
    }
    //去零
    for(p=L->head->next;p->next!=L->head;){
        if(p->next->data.base==0)
            Delp(L,p->next);
        else
            p=p->next;
    }

    //求导
    for(p=L->head->next;p!=L->head;p=p->next){
        p->data.base*=p->data.pow;
        p->data.pow--;
    }
    //输出
    if(!L->len||!L->head->next->data.base)
        printf("%d",0);
    else
        for(p=L->head->next;p!=L->head;p=p->next){
            if(p->data.base==0)
                break;
            if(p==L->head->next){
                if(p->data.base>0)
                    ;
                else
                    printf("- ");
            }
            else 
                printf(" %c ",p->data.base>0?'+':'-');
            if(p->data.pow==0){
                printf("%d",abs(p->data.base));
            }
            else if(p->data.pow==1){
                printf("%dx",abs(p->data.base));
            }
            else{
                printf("%dx^%d",abs(p->data.base),p->data.pow);
            }
        }

    return 0;
}