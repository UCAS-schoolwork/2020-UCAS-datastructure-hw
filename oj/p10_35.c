#include <stdio.h>
#include <stdlib.h>
#define MAX 20000

typedef struct {
    int r[MAX];
    int len;
}Heap;

void swap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

void Adjust(Heap * H,int i, int len){
    if(i>len/2)
        return;
    int left = 2*i;
    int right = left+1;
    if(H->r[i]<H->r[left] || right<=len && H->r[i]<H->r[right]){
        if(right<=len && H->r[left]<H->r[right]){
            swap(&H->r[i],&H->r[right]);
            Adjust(H,right,len);
        }
        else {
            swap(&H->r[i],&H->r[left]);
            Adjust(H,left,len);
        }
    }
}

void HeapSort(Heap * H){

    for (int i = H->len/2; i>0; i--) 
        Adjust(H, i, H->len);
    for (int i = H->len; i>1; i--) {
        swap(&H->r[1], &H->r[i]);
        Adjust(H, 1, i-1);
    }
}

int main()
{
    int dat;
    char c;
    Heap H;
    H.len=0;
    while(scanf("%d%c",&dat,&c)==2){
        H.r[++H.len] = dat;
    }
    HeapSort(&H);
    for(int i=1; i<=H.len;i++)
        printf("%d%c",H.r[i],i==H.len?'\n':',');
    return 0;
}