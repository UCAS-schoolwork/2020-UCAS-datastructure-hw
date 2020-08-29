#include<stdio.h>
#include <ctype.h>
int s[10000];

//Horner Algorithm is fast
int main()
{
    int n,x;
    int i=0;
    scanf("%d%d",&n,&x);
    char c;
   
    while(n-->-1)
    {
        scanf("%d",s+i);
        i++;
    }
    int out=0;
    for(;i>0;){
        out*=x;
        out+=s[--i];
    }
    printf("%d",out);
    return 0;
}