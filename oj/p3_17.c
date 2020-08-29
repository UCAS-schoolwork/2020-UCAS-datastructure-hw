#include <stdio.h>
#include<stdlib.h>

#define Initsize 1000
#define Increment 100
#define True 1
#define False 0

typedef char Status;
typedef char ElemType;

typedef struct SqStack{
    ElemType *top;
    ElemType *base;
    int stacksize;
}Stack;

Stack * InitStack(void){
    Stack *S;
    S = (Stack*)malloc(sizeof(Stack));
    if(!S)  
        return NULL;
    S->base = (ElemType*)malloc(Initsize*sizeof(ElemType));
    if(!S->base)  
        return NULL;
    S->top = S->base;
    S->stacksize = Initsize;
    return S;
}

Status GetTop(Stack *S,ElemType *e)
{
    if(S->top == S->base)
        return False;
    *e = *(S->top-1);
    return True;
}

Status Push(Stack *S,ElemType e)
{
    if(S->top - S->base >= S->stacksize){
        S->base = (ElemType*)realloc(S->base,S->stacksize+=Increment);
        if(!S->base)
            return False;
    }
    *(S->top++) = e;
    return True;
}

Status Pop(Stack *S, ElemType *e)
{
    if(S->top==S->base)
        return False;
    *e = *(--S->top);
    return True;
}

Status isEmpty(Stack *S)
{
    if(S->top==S->base)
        return True;
    return False;
}

int main()
{
    char c,w;
    Stack *S = InitStack();
    while((c=getchar())!='@')
    {
        if(c!='&')
            Push(S,c);
        else
            break;
    }
    while((c=getchar())!='@')
    {
        Pop(S,&w);
        if(w!=c)
            goto Nofound;
    }
    if(isEmpty(S))
        printf("%d",1);
    else
Nofound:
        printf("%d",0);
    return 0;
}

