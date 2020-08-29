#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
typedef char ElemType;
typedef char Status;
//十字链表实现，写了三小时...
typedef struct olnode{
    int i,j;
    ElemType e;
    struct olnode *right, *down;
} OLNode;
typedef OLNode *OLink;

typedef struct{
    OLink *rhead, *chead;
    int mu,nu,tu;
} CrossList;

CrossList * CreatCross(int mu, int nu)
{
    CrossList * M = (CrossList *)malloc(sizeof(CrossList));
    if(!M)
        return NULL;
    M->rhead = (OLink *)malloc((mu+1)*sizeof(OLink));
    M->chead = (OLink *)malloc((nu+1)*sizeof(OLink));
    memset(M->rhead,0,(mu+1)*sizeof(OLink));
    memset(M->chead,0,(nu+1)*sizeof(OLink));
    M->mu = mu;
    M->nu = nu;
    M->tu = 0;
    return M;
}

Status InsertELem(CrossList * M, int i, int j, ElemType e)
{
    if(!e)
        return TRUE;
    OLNode *p = (OLNode *)malloc(sizeof(OLNode));
    OLNode *q;
    if(!p)
        return FALSE;
    p->i = i;
    p->j = j;
    p->e = e;
    p->down = p->right = NULL;
    if(M->rhead[i] == NULL || M->rhead[i]->j>j){
        p->right = M->rhead[i];
        M->rhead[i] = p;
    }
    else{
        for(q=M->rhead[i];(q->right)&&q->right->j<j;q=q->right)
            ;
        p->right = q->right;
        q->right = p;
    }
    if(M->chead[j] == NULL || M->chead[j]->i>i){
        p->down = M->chead[j];
        M->chead[j] = p;
    }
    else{
        for(q=M->chead[j];(q->down)&&q->down->i<i;q=q->down)
            ;
        p->down = q->down;
        q->down = p;
    }
    M->tu++;
    return TRUE;
}

void DeleteElem(CrossList *A, int i, int j)
{
    OLNode *p, *r;
    for(p=A->rhead[i];p&&(p->right)&&p->right->j<j;p=p->right)
        ;
    r = p->right;
    p->right = r->right;
    for(p=A->chead[j];p&&(p->down)&&p->down->i<i;p=p->down)
        ;
    p->down = r->down;
    free(r);
    A->tu--;
}

void AddCross(CrossList *A, CrossList *B)
{
    OLNode *p, *q;
    for(int i=1;i<=B->mu;i++){
        if(!B->rhead[i])
            continue;
        q = A->rhead[i];
        for(p = B->rhead[i];p;p = p->right){
            for(;q&&q->right&&q->j<p->j;q=q->right)
                ;
            if(q&&q->j==p->j){
                if(q->e + p->e == 0)
                    DeleteElem(A, i, p->j);
                else 
                    q->e += p->e;
            }
            else{
                InsertELem(A,i,p->j,p->e);
            }
        }
    }
}

void PrintCross(CrossList *A)
{
    OLNode *p;
    int lastj;
    printf("[");
    for(int i=1;i<=A->mu;i++){
        printf("[");
        if(!A->rhead[i])
            for(int j=1;j<=A->nu;j++)
                printf("0%c",j==A->nu?']':',');
        else{
            lastj=0;
            for(p=A->rhead[i];p;p=p->right){
                for(int j=lastj+1;j<p->j;j++)
                    printf("0%c",j==A->nu?']':',');
                printf("%d%c",p->e,p->j==A->nu?']':',');
                lastj=p->j;
            }
            for(int j=lastj+1;j<=A->nu;j++)
                printf("0%c",j==A->nu?']':',');
        }
        printf("%c",i==A->mu?']':';');
    }
}

int main()
{
    //Input
    char c;
    int mu,nu;
    int choose=0;
    scanf("%d%c",&mu,&c);
    scanf("%d%c",&nu,&c);
    CrossList * A = CreatCross(mu,nu);
    CrossList * B = CreatCross(mu,nu);
    int m,n;
    m=n=1;

    while((c=getchar())!=EOF)
    {
        int sum=0;
        int sign=0;
        if(c=='-'){
            sign = 1;
            goto MINUS;
        }
        if(isdigit(c)){
            sum = c-'0';
MINUS:
            while (isdigit(c=getchar())){
                sum*=10;
                sum+=c-'0';
            }
            if(sign)
                sum=-sum;
            if(!choose)
                InsertELem(A,m,n,sum);
            else 
                InsertELem(B,m,n,sum);
            if(n<nu)
                n++;
            else{
                n=1;
                m++;
            }
        }
        else if(c=='+'){
            choose=1;
            m=n=1;
        }
       
    }
    AddCross(A,B);
    //Output
    PrintCross(A);

    return 0;
}