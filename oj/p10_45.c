#include <stdio.h>
#define MAXSIZE 2000

int cnt[1000];
int buf[MAXSIZE];
int sp;

void CountSort(int s[],int len)
{
    for(int i=0;i<len;i++){
        if(0<=s[i] && s[i]<1000)
            cnt[s[i]]++;
    }
    int j=0;
    for(int i=0;i<len;i++){
        for(;!cnt[j];j++)
            ;
        buf[i] = j;
        cnt[j]--;
    }
}

int main()
{
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2){
        buf[sp++] = dat;
    }
    CountSort(buf,sp);
    for(int i=0;i<sp;i++)
        printf("%03d%c",buf[i],i==sp-1?'\n':' ');
    return 0;
}