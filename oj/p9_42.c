#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 50
typedef char * KeyType;
typedef int Record;
typedef enum Nodekind {LF,BH}NodeKind;
typedef struct TRIENODE{
    NodeKind kind;
    int level;
    union{
        struct{
            KeyType K;
            Record * infoptr;
        }lf;
        struct{
            struct TRIENODE * ptr[27]; 
            int num;
        }bh;
    }uni;
}TrieNode;

int ori(char s)
{
    return s > 'a' ? s-'a'+1 : 0;
}

int InsertKey(TrieNode * T, char * s, int maxlevel)
{
    TrieNode * p = T;
    while(*s && p->level<maxlevel){
        p->uni.bh.num++;
        if(p->kind == BH){ 
            if(!p->uni.bh.ptr[ori(*s)]){
                TrieNode * t = (TrieNode *)malloc(sizeof(TrieNode));
                memset(t,0,sizeof(TrieNode));
                t->kind = BH;
                t->level = p->level+1;
                p->uni.bh.ptr[ori(*s)] = t;
            }
        }
        else if(p->kind == LF)
            return 0;
        p = p->uni.bh.ptr[ori(*s)];
        s++;
    }
    p->uni.bh.num++;
    if(!p->uni.bh.ptr[ori(*s)]){
        TrieNode * t = (TrieNode *)malloc(sizeof(TrieNode));
        memset(t,0,sizeof(TrieNode));
        t->kind = LF;
        p->uni.bh.ptr[ori(*s)] = t;
    }
    return 1;
}

TrieNode * InitTrie(void)
{
    TrieNode * p = (TrieNode *)malloc(sizeof(TrieNode));
    memset(p,0,sizeof(TrieNode));
    p->kind = BH;
    return p;
}

char input[MAXLEN];
int sp=0;

void Travel(TrieNode * T)
{
    if(!T || T->kind == LF)
        return;
    input[sp++] = T->uni.bh.num;
    for(int i=0;i<27;i++){
        if(T->uni.bh.ptr[i])
            Travel(T->uni.bh.ptr[i]);
    }
    return;
}
int main()
{
    TrieNode * T = InitTrie();
    int dat;
    char c;
    scanf("%d",&dat);
    getchar();
    while(1){
        c=getchar();
        if(c==';'||c=='\n'||c==EOF){
            input[sp] = 0;
            sp = 0;
            InsertKey(T,input,dat);
            if(c=='\n'||c==EOF)
                break;
        }
        else {
            input[sp++] = c;
        }
    }
    sp=0;
    Travel(T);
    for(int i=1;i<sp;i++)
        printf("%d%c",input[i],i==sp-1?'\n':',');

    return 0;
}