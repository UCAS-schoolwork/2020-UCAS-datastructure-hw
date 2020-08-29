#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef int ElemType;
//字母，链表，数字
typedef enum {ATOM, LIST,NUM} ElemTag;
typedef struct GLNode{
    ElemTag tag;
    union {
        ElemType atom;
        struct {
            struct GLNode *hp, *tp;
        } ptr;
    };
} *GList, GNode;

char *GetHead(char *s)
{
    char *p=s;
    char *s0=s;
    if(!s||*s==0)
        return NULL;
    int len = strlen(s);
    p = (char *)malloc(sizeof(char)*len);
    strcpy(p,s);
    int i=0;
    while(*s){
        if(*s=='(')
            i++;
        else if(*s==')')
            i--;
        else if(*s==','&&i==1)
            break;
        s++;
    }
    if(*s){
        *(p+(s-s0))=0;
        p++;
    }
    else{
        *(p+len-1)=0;
        p++;
    }
    return p;
}


char *GetTail(char *s)
{
    char *p=s;
    char *s0=s;
    if(!s||*s==0)
        return NULL;
    int len = strlen(s);
    p = (char *)malloc(sizeof(char)*len+1);
    strcpy(p,s);
    int i=0;
    while(*s){
        if(*s=='(')
            i++;
        else if(*s==')')
            i--;
        else if(*s==','&&i==1)
            break;
        s++;
    }
    if(*s){
        *(p+(s-s0))='(';
        p+=(s-s0);
    }
    else
        return NULL;
    return p;
}

int nocomma(char *s)
{
    while(*s++)
        if(*s==',' || *s=='(' || *s==')')
            return 0;
    return 1;
}

GNode * InitGList(char *s)
{
    if(!s||!*s)
        return NULL;
    GNode * L = (GNode *)malloc(sizeof(GNode));

    if(nocomma(s)){
        
        if(isalpha(*s)){
            L->tag = ATOM;
            L->atom = *s;
        }
        else{
            L->tag = NUM;
            L->atom = atoi(s);
        }
        
    }
    else{
        L->tag = LIST;
        GNode * p = L;
        p->ptr.hp = InitGList(GetHead(s));
        p->ptr.tp = InitGList(GetTail(s));
    }
    return L;
}

int DeleteElem(GNode * L, int e, ElemTag Tag)
{
    if(!L)
        return 1;
    if(L->tag == LIST){
        if(L->ptr.hp && L->ptr.hp->tag == Tag && L->ptr.hp->atom == e){
            free(L->ptr.hp);
            L->ptr.hp = NULL;
        }
        else 
            DeleteElem(L->ptr.hp,e,Tag);
        DeleteElem(L->ptr.tp,e,Tag);
    }
    return 1;
}

void PrintGL(GNode *L,int mode)
{
    if(!L)
        return;
    if(L->tag == ATOM)
        printf("%c",L->atom);
    else if(L->tag == NUM)
        printf("%d",L->atom);
    else if(L->ptr.hp){
        if(mode)
            printf("(");
        PrintGL(L->ptr.hp,1);
        if(L->ptr.tp){
            if(L->ptr.tp->ptr.hp||L->ptr.tp->ptr.tp)
                printf(",");
            PrintGL(L->ptr.tp,0);
        }
        if(mode)
            printf(")");
    }
    else if(L->ptr.tp){
        if(mode)
            printf("(");
        PrintGL(L->ptr.tp,0);
        if(mode)
            printf(")");
    }
    else
        if(mode)
            printf("()");    
    
    return;
}

char s[200] = {0};
int main()
{
    int i=0;
    int tar;
    ElemTag Tag = NUM;
    char c;
    while((c=getchar())!=';'){
        s[i++]=c;
    }
    if(isalpha(s[0])){
        tar = s[0];
        Tag = ATOM;
    }
    else
        tar = atoi(s);
    scanf("%s",s);
    GNode * L = InitGList(s);
    DeleteElem(L,tar,Tag);
    PrintGL(L,1);
    return 0;
}