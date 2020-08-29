#include <stdio.h>
#include<stdlib.h>
#include<ctype.h>

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

ElemType GetTop(Stack *S)
{
    if(S->top == S->base)
        return 0;
    return *(S->top-1);
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

ElemType Pop(Stack *S)
{
    if(S->top==S->base){
        return 0;
    }
    return *(--S->top);
}

Status isEmpty(Stack *S)
{
    if(S->top==S->base)
        return True;
    return False;
}

int weight[256];
int main()
{
    char c;
    weight['*'] = weight['/'] = 1;
    weight[0]=weight['(']=-1;
    Stack *S1 = InitStack();
    Stack *S2 = InitStack();
    while((c=getchar())!=EOF)
    {
        if(c=='+'||c=='-'||c=='/'||c=='*'){
            
            while(weight[c]<=weight[GetTop(S2)])
                Push(S1,Pop(S2));
            Push(S2,c);
        }
        else if(isalpha(c))
            Push(S1,c);
        else if(c==')'){
            while((c=Pop(S2))!='('&&c!=0)
                Push(S1,c);
        }
        else if(c=='(')
            Push(S2,c);
    }
    while((c=Pop(S2))!=0)
        Push(S1,c);
    for(ElemType *w=S1->base;w<S1->top;w++){
        printf("%c",*w);
    }

    return 0;
}

