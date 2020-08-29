#include <stdio.h>
#include <string.h>
#define MAXSIZE 2000

int c[MAXSIZE];
int buf[MAXSIZE];
int tmp[MAXSIZE];
int sp;

void CountSort(int s[],int len)
{
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            if(s[i]>s[j])
                c[i]++;
            else 
                c[j]++;
        }
    }
    memcpy(tmp,s,len*sizeof(int));
    for(int i=0;i<len;i++){
        s[c[i]] = tmp[i];
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
        printf("%d%c",buf[i],i==sp-1?'\n':' ');
    return 0;
}