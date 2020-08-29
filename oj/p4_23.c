#include <stdio.h>
#include <stdlib.h>

#define CHUNKSIZE 80

typedef struct chunk{
    char ch[CHUNKSIZE];
    struct chunk *next;
    struct chunk *prior;
} Chunk;

typedef struct{
    Chunk *head;
    Chunk *tail;
    int curlen;
    int cnum;
} LString;

LString * InitLString()
{
    LString * L = (LString *)malloc(sizeof(LString));
    Chunk * C = (Chunk *)malloc(sizeof(Chunk));
    C->next = C->prior = NULL;
    L->head = L->tail = C;
    L->curlen = 0;
    L->cnum = 0;
    return L;
}

int AddChar(LString *L, char c)
{
    if(L->curlen == CHUNKSIZE){
        Chunk * C = (Chunk *)malloc(sizeof(Chunk));
        L->tail->next = C;
        C->prior = L->tail;
        L->tail = C;
        C->next = NULL;
        L->curlen = 0;
        L->cnum++;
    }
    L->tail->ch[L->curlen++] = c;
    return 1;
}


int main()
{
    LString * L = InitLString();
    int c;
    while((c=getchar())!=EOF && c!='\n'){
        AddChar(L,c);
    }
    Chunk *A = L->head;
    Chunk *B = L->tail;
    int hh = 0;
    int tt = L->curlen-1;
    int yes = 1;
    int total = (L->cnum) * CHUNKSIZE + L->curlen-1;
    int i=0;
    for(;i<=total/2;i++){
        if(A->ch[hh]!=B->ch[tt]){
            yes=0;
            break;
        }
        if(hh>=CHUNKSIZE-1){
            A = A->next;
            hh=0;
        }
        else 
            hh++;
        if(tt==0){
            B = B->prior;
            tt = CHUNKSIZE-1;
        }
        else 
            tt--;
    }
    printf("%s",yes?"Yes":"No");

    return 0;
}
