#include <stdio.h>
#define MAXSIZE 20000

int buf[MAXSIZE];
int sp;

void change(int *i, int *j)
{
    int t=*i;
    *i=*j;
    *j=t;
}

void Insertsort(int s[],int len)
{
    for(int i=1;i<len;i++){
        int j;
        for(j=i-1;j>=0&&s[j]>s[j+1];j--){
            change(&s[j+1],&s[j]);
        }
    }
}

int Quicksort(int s[],int len)
{
    int head = 0;
    int tail = len-1;
    int left = 1;
    while(sp>0 || left==1){
        if(!left){
            tail=buf[--sp];
            head=buf[--sp];
        }
        if(tail-head<3 && tail>head)
            Insertsort(s+head,tail-head+1);
        else if(tail-head>=3){
            int last=head+1;
            for(int i=head+1;i<=tail;i++){
                if(s[i]<s[head]){
                    change(&s[i],&s[last]);
                    last++;
                }
            }
            last--;
            change(&s[last],&s[head]);
            buf[sp++]=last+1;
            buf[sp++]=tail;
            tail = last-1;
            left=1;
            continue;
        }
        left=0;
    }
    return 1;
}

int s[MAXSIZE];
int sp1;
int main()
{
    int dat;
    char c;
    while(scanf("%d%c",&dat,&c)==2){
        s[sp1++] = dat;
    }
    Quicksort(s,sp1);
    for(int i=0;i<sp1;i++)
        printf("%d%c",s[i],i==sp1-1?'\n':',');
    return 0;
}